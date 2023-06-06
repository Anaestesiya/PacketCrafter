#ifndef DHCP_DISCOVERY_H
#define DHCP_DISCOVERY_H

#include "scenarios/scenario.h"

#include <QProcess>
#include <QTemporaryFile>
#include <QVBoxLayout>
#include <QMessageBox>

#include <protoFields/udp.h>
#include <protoFields/dhcp.h>

#define SCRIPT_NAME ":/scenarios/python_scripts/dhcp.py"
#define ARGS_REQUIRED(newIP, iface) ("--new_ip " + newIP + " --iface " + iface)

class DHCP_Discovery : public Scenario, CDHCP, CUDP
{
public:

    DHCP_Discovery(QVBoxLayout * parentFrame, QPushButton *srcButton);

    int startScenario(QString Ifc) override
    {
//        if (validatedstIP() == -1) return -1;
//        if (validateSrcIP() == -1) return -1;

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
        arguments = ARGS_REQUIRED(newIP.text(), Ifc);

        qDebug() << arguments;

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

    ~DHCP_Discovery();
};

#endif // DHCP_DISCOVERY_H
