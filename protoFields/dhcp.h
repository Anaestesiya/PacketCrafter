#ifndef CDHCP_H
#define CDHCP_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QComboBox>
#include <QStringList>

#include "cfields.h"

#define DHCP_FORMAT "DHCP=DHCP("

class CDHCP : public CFields
{
public:
    QComboBox type;
    CDHCP(QVBoxLayout *parentFrame);
    QLineEdit newIP;

    QRegularExpression ipv4AddressRegex;

    static QHash<QString, int> *dhcptypes;

    static void fillTypes()
    {
        dhcptypes->insert("discovery", 0);
        dhcptypes->insert("request", 3);
        dhcptypes->insert("offer", 4);
        dhcptypes->insert("ack", 5);
        dhcptypes->insert("release", 8);
    }

    QByteArray macToBytes(const QString& macAddress)
    {
        QByteArray bytes;
        QStringList parts = macAddress.split(':');

        foreach (const QString& part, parts) {
            bool ok;
            quint8 byte = part.toInt(&ok, 16);
            if (ok) {
                bytes.append(byte);
            } else {
                // Invalid MAC address format, handle the error
                bytes.clear();
                break;
            }
        }

        return bytes;
    }

    QString format() override
    {

        QString format = "chaddr=int(ether.src.replace(':', ''), 16).to_bytes(6, 'big')";
        format += "BOOTP(chaddr=chaddr)/";
        format += "DHCP(options=[('message-type', 'request'), ('requested_addr', ";
        format += newIP.text();
        format += "), 'end'])";

        return format;
    }
};


#endif // CICMP_H
