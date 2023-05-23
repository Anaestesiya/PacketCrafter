#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDialog>

#include "packethandler.h"
#include "protoFields/etherfields.h"
#include "protoFields/ipv4fields.h"
#include "protoFields/ipv6fields.h"
#include "protoFields/chttp.h"
#include "protoFields/icmp.h"
#include "protoFields/tcp.h"
#include "protoFields/udp.h"
#include "protoFields/arp.h"

#include "savefiledialog.h"
#include "scenarioswindow.h"
#include "clogger.h"

#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int res = translator.load("PacketCrafter_uk_UA");
    if (res < 0)
        LOG_ERROR("Failed to load translator");
    qApp->installTranslator(&translator);

    layer_groups[0] = (QGridLayout *)(ui->groupBox_application->layout());
    layer_groups[1] = (QGridLayout *)(ui->groupBox_transport->layout());
    layer_groups[2] = (QGridLayout *)(ui->groupBox_internet->layout());
    layer_groups[3] = (QGridLayout *)(ui->groupBox_link->layout());
    layer_groups[4] = (QGridLayout *)(ui->groupBox_physical->layout());

    // fill protos

    for (int i = APPLICATION; i <= PHYSICAL; i++) {
        QGridLayout *grp = layer_groups[i - 1];
        for (int k = 0; k < grp->count(); ++k)
        {
            // Let ICMP be as TCP layer
            if (!static_cast<CProtocol *>(grp->itemAt(k)->widget())->text().startsWith("ICMP"))
                static_cast<CProtocol *>(grp->itemAt(k)->widget())->layer = (ELayer)(i);
            else static_cast<CProtocol *>(grp->itemAt(k)->widget())->layer = (ELayer)(i-1);
        }
    }
    ui->spinBox_count->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_count->setRange(1, 10000);

    ui->spinBox_period->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_period->setRange(1,10);
    LOG_INFO("Init Application successfully");
}

MainWindow::~MainWindow()
{
    LOG_INFO("End App");
    delete ui;
}


void MainWindow::on_pushButton_set_UA_clicked()
{
    LOG_INFO("Change language to UA");
    // toggle effect
    ui->pushButton_set_UA->setEnabled(false);
    ui->pushButton_set_EN->setEnabled(true);
    // ToDo: set translation

    translator.load("PacketCrafter_uk_UA");
    qApp->installTranslator(&translator);

    ui->retranslateUi(this);
}


void MainWindow::on_pushButton_set_EN_clicked()
{
    LOG_INFO("Change language to EN");

    // toggle effect
    ui->pushButton_set_EN->setEnabled(false);
    ui->pushButton_set_UA->setEnabled(true);
    // ToDo: set translation
    translator.load("PacketCrafter_en_US");
    qApp->installTranslator(&translator);

    ui->retranslateUi(this);
}

void MainWindow::addProtoAction(CProtocol *proto, CFields *fields)
{
    LOG_INFO("%s is added", proto->text().toStdString().c_str());
    qDebug() << proto->text().toStdString().c_str();
    // Init widget
    CProtocol *packetproto = new CProtocol();
    packetproto->fields = fields;
    packetproto->setGeometry(proto->geometry());
    packetproto->setText(proto->text());
    packetproto->layer = proto->layer;
    packetproto->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    packetproto->setMinimumHeight(75);
    connect(packetproto, SIGNAL(clicked()),this, SLOT(clickedPacketProto()));


    // Filter alogorithm
    QGridLayout *grp = (QGridLayout *)proto->parentWidget()->layout();

    if (proto->parentWidget() != ui->groupBox_internet)
    {
        for (int i = 0; i < grp->count(); ++i)
        {
            static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(false);
            LOG_INFO("%s is not functional anymore", static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().toStdString().c_str());
        }
    }
    else
    {
        for (int i = 0; i < grp->count(); ++i)
        {
            if (proto->text().contains("v6") && !static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().contains("v6"))
            {
                static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(false);
                LOG_INFO("%s is not functional anymore", static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().toStdString().c_str());
            }
            else if (!proto->text().contains("v6") && static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().contains("v6"))
            {
                static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(false);
                LOG_INFO("%s is not functional anymore", static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().toStdString().c_str());
            }
            proto->setEnabled(false);
        }
    }

    int index = 1;
    for (int i = 1; i < ui->verticalLayout_packet->count(); ++i)
    {
        index = i;
        QWidget *itemSort = ui->verticalLayout_packet->itemAt(i)->widget();
        qDebug() << packetproto->layer << " " << ((CProtocol *)itemSort)->layer;
        if (packetproto->layer < ((CProtocol *)itemSort)->layer)
            break;
        else index = index + 1;
    }

    ui->verticalLayout_packet->insertWidget(index, packetproto);
    if (packetproto->fields) {
        ui->verticalLayout_fields->insertWidget(index - 1, &packetproto->fields->grpbox);
        LOG_INFO("Add headers for %s", packetproto->fields->grpbox.title().toStdString().c_str());
    }

    ui->verticalLayout_packet->setAlignment(Qt::AlignCenter);

    packetproto->show();

    // Init custom fileds layout

}

// Remove widget from Packet layout when clicked
void MainWindow::clickedPacketProto()
{
    LOG_INFO("Delete %s of layer %s",((CProtocol *)sender())->text().toStdString().c_str(), ((CProtocol *)sender())->layer);
    QGridLayout *grp = layer_groups[((CProtocol *)sender())->layer - 1];
    if (((CProtocol *)sender())->text().contains("ICMP"))
        grp = layer_groups[((CProtocol *)sender())->layer];
    for (int i = 0; i < grp->count(); ++i)
    {
        static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(true);
        LOG_INFO("%s is back to enabled", static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().toStdString().c_str());
    }

    ((CProtocol*)sender())->hide();
    ui->verticalLayout_packet->removeWidget((CProtocol*)sender());

    if (((CProtocol *)sender())->fields != nullptr)
    {
        ((CProtocol *)sender())->fields->grpbox.hide();
        ui->verticalLayout_fields->removeWidget(&((CProtocol *)sender())->fields->grpbox);
        delete ((CProtocol *)sender())->fields;
    }
    delete sender();
    LOG_DEBUG("Delete sender");
}

// Ethernet
void MainWindow::on_pushButton_14_clicked()
{
    addProtoAction(ui->pushButton_14, new CEtherFields(ui->verticalLayout_fields));
}

// PPP
void MainWindow::on_pushButton_13_clicked()
{
    addProtoAction(ui->pushButton_13);
}

// ARP
void MainWindow::on_pushButton_11_clicked()
{
    addProtoAction(ui->pushButton_11, new CARP(ui->verticalLayout_fields));
}

// IPv4
void MainWindow::on_pushButton_10_clicked()
{
    addProtoAction(ui->pushButton_10, new CIpv4fields(ui->verticalLayout_fields));
}

// IPv6
void MainWindow::on_pushButton_15_clicked()
{
    addProtoAction(ui->pushButton_15, new CIPv6fields(ui->verticalLayout_fields));
}

// ICMP
void MainWindow::on_pushButton_12_clicked()
{
    addProtoAction(ui->pushButton_12, new Cicmp(ui->verticalLayout_fields));
}

// ICMPv6
void MainWindow::on_pushButton_16_clicked()
{
    addProtoAction(ui->pushButton_16);
}


// TCP
void MainWindow::on_pushButton_8_clicked()
{
    addProtoAction(ui->pushButton_8, new CTCP(ui->verticalLayout_fields));
}

// UDP
void MainWindow::on_pushButton_9_clicked()
{
    addProtoAction(ui->pushButton_9, new CUDP(ui->verticalLayout_fields));
}

/*
 *     QProcess process;
    process.start("/home/anastasiiafrolova/send_ssdp.py");
    process.waitForFinished();

    QString output(process.readAllStandardOutput());
    qDebug()<<output;

    QString err(process.readAllStandardError());
    qDebug()<<err;
*/

// HTTP
void MainWindow::on_pushButton_5_clicked()
{
    addProtoAction(ui->pushButton_5, new Chttp(ui->verticalLayout_fields));
}

// FTP
void MainWindow::on_pushButton_7_clicked()
{
    addProtoAction(ui->pushButton_7);
}

// DNS
void MainWindow::on_pushButton_6_clicked()
{
    addProtoAction(ui->pushButton_6);
}

// DHCP
void MainWindow::on_pushButton_17_clicked()
{
    addProtoAction(ui->pushButton_17);
}

void MainWindow::validateParams()
{
    LOG_DEBUG("In %s", __FUNCTION__);
    packetHandler.protoVector.clear();
    for (int i = 1; i < ui->verticalLayout_packet->count(); ++i)
    {
        QWidget *itemSort = ui->verticalLayout_packet->itemAt(i)->widget();
        packetHandler.protoVector.append(((CProtocol *)itemSort)->fields);
    }
    std::reverse(packetHandler.protoVector.begin(), packetHandler.protoVector.end());
}

// send button
void MainWindow::on_pushButton_2_clicked()
{
    LOG_DEBUG("In %s", __FUNCTION__);
    LOG_INFO("Press send");
    QRegularExpression emptyRegex("^\\s*$"); // Regular expression to check for empty input
    QPalette palette = ui->lineEdit_Ifc->palette();
    if (ui->lineEdit_Ifc->text().isEmpty() || ui->lineEdit_Ifc->text().contains(emptyRegex)) {
        // Input is empty or contains only whitespace characters
        palette.setColor(QPalette::Base, Qt::red); // Set the background color to red
        ui->lineEdit_Ifc->setPalette(palette);
        LOG_WARNING("Interface field is incorrect");
        return;
    } else {
        // Input is not empty
        LOG_DEBUG("Interface is OK");
        palette.setColor(QPalette::Base, Qt::white); // Set the background color to white
    }
    ui->lineEdit_Ifc->setPalette(palette);

    validateParams();

    QString scriptname = packetHandler.formatProtos();
    if (scriptname == "")
    {
        LOG_ERROR("Script name is empty");
        return;
    }
    packetHandler.Ifc = ui->lineEdit_Ifc->text();
    packetHandler.period = ui->spinBox_period->value();
    packetHandler.packetCount = ui->spinBox_count->value();

    packetHandler.sendPacket(scriptname);
}

// TODOs

// 1. add "Autofill strings to lineedits as a hint"
// 2. add default values to particular fields
// 3. add validations for packets
// 4. Varify packet
// 6. Auto open wireshark to look for traffic ?

// 5. Open and parse file
// 7. Add logging


// Save packets
void MainWindow::on_pushButton_3_clicked()
{
    LOG_DEBUG(__FUNCTION__);
    validateParams();
    QString scriptname = packetHandler.formatProtos();
    QString packet = packetHandler.packet;
    if (scriptname == "")
        return;

    SaveFileDialog dialog;
    QObject::connect(&dialog, &SaveFileDialog::saveFile, [packet, scriptname](const QString& filePath, bool isBinaryFormat) {
        if (isBinaryFormat)
        {
            // Save file as binary format
            // Add your binary format handling code here
            qDebug() << "Saving file as binary format: " << filePath;
            qDebug() << packet << " " << scriptname;

            QString script = "from scapy.all import *\n";
            script += packet + "\n";
            script += "binary_data = bytes(packet)\n";
            script += "with open('" + filePath + "', 'wb') as file:\n";
            script += "    file.write(binary_data)";

            QStringList arguments;
            arguments << "-c" << script;

            QProcess scapyProcess;
            scapyProcess.start("python3", arguments);
            if (scapyProcess.waitForFinished())
            {
                QString output(scapyProcess.readAllStandardOutput());
                qDebug()<<output;

                QString err(scapyProcess.readAllStandardError());
                qDebug()<<err;
            }
        }
        else
        {
            // Save file as text format
            // Add your text format handling code here
            qDebug() << "Saving file as text format: " << filePath;

            // Create a QFile object for the source file
            QFile sourceFile(scriptname);

            // Open the source file in ReadOnly mode
            if (!sourceFile.open(QIODevice::ReadOnly))
            {
                qDebug() << "Failed to open source file.";
                return false;
            }

            // Create a QFile object for the destination file
            QFile destinationFile(filePath);

            // Open the destination file in WriteOnly mode
            if (!destinationFile.open(QIODevice::WriteOnly))
            {
                qDebug() << "Failed to open destination file.";
                sourceFile.close();
                return false;
            }

            // Read the contents of the source file
            QByteArray fileData = sourceFile.readAll();

            // Write the contents to the destination file
            qint64 bytesWritten = destinationFile.write(fileData);

            // Close the source and destination files
            sourceFile.close();
            destinationFile.close();

            // Check if the bytes written matches the file size
            if (bytesWritten != fileData.size())
            {
                qDebug() << "Failed to copy the file.";
                return false;
            }

            qDebug() << "File copied successfully.";
        }
    });

    if (dialog.exec() == QDialog::Accepted)
    {
        // Dialog was accepted, continue with the chosen file path
        // Add any additional code here if needed
    }
}

// Packet scenarios
void MainWindow::on_pushButton_clicked()
{
    LOG_DEBUG(__FUNCTION__);
    ScenariosWindow *sw = new ScenariosWindow();
    sw->m = this;
    sw->show();
    this->hide();
}

// log button
void MainWindow::on_pushButton_18_clicked()
{
    LOG_DEBUG(__FUNCTION__);
    FileDisplayer fileDisplayer;

    fileDisplayer.exec();

}

