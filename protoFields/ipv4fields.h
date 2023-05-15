#ifndef IPV4FIELDS_H
#define IPV4FIELDS_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>

#include "cfields.h"

#define IPV4_FORMAT "ip=IP(src='%s', dst='%s', ttl=%d)"

class CIpv4fields : public CFields
{
public:
    QLineEdit srcIP;
    QLineEdit dstIP;
    QSpinBox TTL;

    QString format() override
    {
        QString format = IPV4_FORMAT;
        //        if (srcMac.text() != "")
        //            format += "src=" + srcMac.text();
        //        if (dstMac.text() != "")
        //            format += ", dst=" + dstMac.text();
        format += ")";

        return format;
    }

    CIpv4fields(QVBoxLayout *parentFrame);
    ~CIpv4fields(){}
};

#endif // IPV4FIELDS_H
