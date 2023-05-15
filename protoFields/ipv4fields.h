#ifndef IPV4FIELDS_H
#define IPV4FIELDS_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>

#include "cfields.h"

#define IPV4_FORMAT "ip=IP("

class CIpv4fields : public CFields
{
public:
    QLineEdit srcIP;
    QLineEdit dstIP;
    QSpinBox TTL;

    QRegularExpression ipv4AddressRegex;

    QString format() override
    {
        QPalette palette = dstIP.palette();
        if (dstIP.text().isEmpty() || !dstIP.text().contains(ipv4AddressRegex)) {
            // Input is empty or contains only whitespace characters
            palette.setColor(QPalette::Base, Qt::red); // Set the background color to red
            dstIP.setPalette(palette);
            return "";
        } else {
            // Input is not empty
            palette.setColor(QPalette::Base, Qt::white); // Set the background color to white
        }
        dstIP.setPalette(palette);

        palette = srcIP.palette();
        if (!srcIP.text().isEmpty() && !srcIP.text().contains(ipv4AddressRegex)) {
            // Input is empty or contains only whitespace characters
            palette.setColor(QPalette::Base, Qt::red); // Set the background color to red
            srcIP.setPalette(palette);
            return "";
        } else {
            // Input is not empty
            palette.setColor(QPalette::Base, Qt::white); // Set the background color to white
        }
        srcIP.setPalette(palette);


        QString format = IPV4_FORMAT;
        if (srcIP.text() != "")
            format += "src='" + srcIP.text() + "', ";

        format += "dst='" + dstIP.text() + "', ";
        format += "ttl=" + QString::number(TTL.value());
        format += ")";

        return format;
    }

    CIpv4fields(QVBoxLayout *parentFrame);
    ~CIpv4fields(){}
};

#endif // IPV4FIELDS_H
