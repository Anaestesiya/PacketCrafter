#ifndef TCP_HANDSHAKE_H
#define TCP_HANDSHAKE_H

#include "scenarios/scenario.h"

#include <QProcess>
#include <QTemporaryFile>
#include <QVBoxLayout>
#include <QMessageBox>

#include <protoFields/ipv4fields.h>
#include <protoFields/tcp.h>

#define SCRIPT_NAME ":/scenarios/python_scripts/tcp_handhsake.py"
#define ARGS_REQUIRED(dstip, srcport, dstport, iface) ("--dst_ip " + dstip + " --dst_port " + dstport + " --iface " + iface + " --src_port " + srcport)
#define ARGS_SRCIP(srcip) ("--src_ip " + srcip)

class TCP_handshake : public Scenario, CTCP, CIpv4fields
{
public:

    TCP_handshake(QVBoxLayout * parentFrame, QPushButton *srcButton);

    int startScenario(QString Ifc) override
    {
        if (validatedstIP() == -1) return -1;
        if (validateSrcIP() == -1) return -1;

        QTemporaryFile tempFile;
        if (tempFile.open())
        {
            QFile resourceFile(SCRIPT_NAME);
            if (resourceFile.open(QIODevice::ReadOnly))
            {
                tempFile.write(resourceFile.readAll());
                tempFile.flush();
                resourceFile.close();
            }
            tempFile.close();
        }

        // Execute the Python script
        QProcess pythonScript;
        QString arguments;
        arguments = ARGS_REQUIRED(dstIP.text(), srcPort.text(), dstPort.text(), Ifc);
        if (srcIP.text() != "")
            arguments += " " + ARGS_SRCIP(srcIP.text());

        qDebug() << arguments;
//        pythonScript.start("python3", QStringList() << tempFile.fileName() << ARGS_REQUIRED(dstIP.text(), srcPort.text(), dstPort.text(), Ifc));
        pythonScript.startCommand("python3 " + tempFile.fileName() + " " + arguments);
        if (pythonScript.waitForFinished())
        {
            // Read the output and error messages
            QByteArray outputData = pythonScript.readAllStandardOutput();
            QByteArray errorData = pythonScript.readAllStandardError();

            // Check the exit code of the process
            int exitCode = pythonScript.exitCode();
            if (exitCode == 0) {
                // Execution was successful, show output message
                QMessageBox::information(nullptr, "Success", QString(outputData));
            } else {
                // Execution failed, show error message
                QMessageBox::critical(nullptr, "Error", QString(errorData));
            }
        }
        // Delete the temporary file
        QFile::remove(tempFile.fileName());

        return 0;
    }

    ~TCP_handshake();
};

#endif // TCP_HANDSHAKE_H
