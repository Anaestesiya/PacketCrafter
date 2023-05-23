#include "packethandler.h"

#include <QProcess>
#include <QFile>
#include <QDateTime>
#include <iostream>
#include "clogger.h"
#include <QPushButton>
#include <QTimer>

#define FILENAME_FORMAT ("/tmp/script" + QString::number(QDateTime::currentMSecsSinceEpoch()))

CPacketHandler::CPacketHandler(QWidget *parent) :
    Ifc("lo"),
    process_(nullptr),
    QWidget(parent),
    messageBox_(nullptr),
    progressDialog_(nullptr)
{

}

QString CPacketHandler::formatProtos()
{
    LOG_DEBUG(__FUNCTION__);
    QString script("#!/usr/bin/python3\nfrom scapy.all import *\n");
    QString packet("packet=");
    foreach (auto proto, this->protoVector) {
        QString format = proto->format();
        if (format == "")
            return "";
        script += format + "\n";
        packet += format.left(format.indexOf('=')) + "/";
    }
    packet.chop(1);
    this->packet = script+packet;
    LOG_DEBUG("Packet content is %s", packet.toStdString().c_str());
    LOG_DEBUG("script content is %s", script.toStdString().c_str());

    QFile file(FILENAME_FORMAT);
    if (file.open(QIODevice::ReadWrite)) {
        LOG_DEBUG("Input content to %s", file.fileName().toStdString().c_str());
        QTextStream stream(&file);
        stream << script << "\n";
        stream << packet << "\n";
        file.close();
    }

    return file.fileName();
}

int CPacketHandler::sendPacket()
{
    LOG_DEBUG("start %s", __FUNCTION__);
    QString filename = this->formatProtos();
    if (filename == "")
    {
        LOG_ERROR("Script name is empty");
        return -1;
    }

    progress = 0;

    QString num_packets = QString("num_packets = %1").arg(this->packetCount);
    QString delay = QString("delay = %1").arg((float)(1 / this->period));
    QString sendLine = QString("for _ in range(num_packets):\n"
                               "    sendp(packet,iface='%1')\n"
                               "    time.sleep(delay)").arg(this->Ifc);
    QFile file(filename);
    if (file.open(QIODevice::Append)) {
        QTextStream stream(&file);
        stream << num_packets << "\n";
        stream << delay << "\n";
        stream << sendLine << "\n";
        file.close();
    }
    else {
        LOG_ERROR("Could not open the file");
    }
    if (process_ != nullptr)
        delete process_;
    process_ = new QProcess(this);

    if (progressDialog_ != nullptr)
        delete progressDialog_;
    progressDialog_ = new QProgressDialog(this);

    progressDialog_->setLabelText("Loading...");
    progressDialog_->setCancelButton(nullptr);
    progressDialog_->setWindowModality(Qt::WindowModal);
    progressDialog_->setCancelButton(new QPushButton("Cancel", progressDialog_));
    progressDialog_->setAutoClose(true);

    connect(progressDialog_, &QProgressDialog::canceled, this, &CPacketHandler::onProgressDialogCanceled);
    connect(process_, &QProcess::readyReadStandardOutput, this, &CPacketHandler::onReadyReadStandardOutput);
    connect(process_, &QProcess::readyReadStandardError, this, &CPacketHandler::onReadyReadStandardError);
    connect(process_, &QProcess::finished, this, &CPacketHandler::onProcessFinished);

    QTimer::singleShot(500, this, &CPacketHandler::showProgressDialog);
    process_->start("/usr/bin/python3", QStringList() << filename);

    LOG_DEBUG("end %s", __FUNCTION__);
    return 0;
}

void CPacketHandler::onReadyReadStandardOutput()
{
    QByteArray outputData = process_->readAllStandardOutput();
    if (outputData.isEmpty())
        return;
    if (outputData == ".")
    {
        progress += (int)(100 / packetCount);
        progressDialog_->setValue(progress);
        return;
    }
    QMessageBox::information(nullptr, "Success",QString(outputData));
    LOG_INFO("%s",outputData.toStdString().c_str());
}

void CPacketHandler::onReadyReadStandardError()
{
    QByteArray errorData = process_->readAllStandardError();
    // Update the content of the messageBox_
    if (errorData.isEmpty())
        return;
    QMessageBox::critical(nullptr, "Error",QString(errorData));
    LOG_ERROR("%s",errorData.toStdString().c_str());
    progressDialog_->hide();
}
void CPacketHandler::onProcessFinished()
{
    LOG_INFO("execution completed");
    // Hide the progress dialog when the process has finished
    progressDialog_->hide();

}

void CPacketHandler::showProgressDialog()
{
    qDebug() << "Show progress\n";
    // Show the progress dialog
    progressDialog_->show();
}
void CPacketHandler::onProgressDialogCanceled()
{
    qDebug() << "Process is canceled\n";
    process_->kill();  // Terminate the process if the dialog is canceled
    progressDialog_->hide();
}
