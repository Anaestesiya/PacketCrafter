#include "packethandler.h"

#include <QProcess>
#include <QFile>
#include <QDateTime>
#include <iostream>

#define FILENAME_FORMAT ("/tmp/script" + QString::number(QDateTime::currentMSecsSinceEpoch()))

CPacketHandler::CPacketHandler() : Ifc("lo")
{

}

QString CPacketHandler::formatProtos()
{
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

    qDebug() << script << "\n";
    qDebug() << packet << "\n";

    QFile file(FILENAME_FORMAT);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << script << "\n";
        stream << packet << "\n";
        file.close();
    }

    return file.fileName();
}

int CPacketHandler::sendPacket(QString filename)
{
    QString sendLine = QString("sendp(packet,iface='%1')").arg(this->Ifc);
    QFile file(filename);
    if (file.open(QIODevice::Append)) {
        QTextStream stream(&file);
        stream << sendLine << "\n";
        file.close();
    }
    else {
        qDebug() << "Could not open the file\n";
    }

    QProcess process;
    process.start("/usr/bin/python3", QStringList() << filename);
    if (process.waitForFinished())
    {
        QString output(process.readAllStandardOutput());
        qDebug()<<output;

        QString err(process.readAllStandardError());
        qDebug()<<err;
    }

}
