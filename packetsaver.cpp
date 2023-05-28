#include "packetsaver.h"
#include "clogger.h"
#include "packetvalidator.h"
#include "savefiledialog.h"
#include "packethandler.h"

PacketSaver::PacketSaver()
{

}

void PacketSaver::savePacket(CPacketHandler &packetHandler)
{
    LOG_DEBUG(__FUNCTION__);

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
    }
}
