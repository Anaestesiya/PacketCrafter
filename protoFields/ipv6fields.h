#ifndef CIPV6FIELDS_H
#define CIPV6FIELDS_H


#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>

#include "cfields.h"

#define IPV6_FORMAT "ip=IPv6(src='%s', dst='%s', ttl=%d)"

class CIPv6fields : public CFields
{
public:
    QLineEdit srcIP;
    QLineEdit dstIP;
    QSpinBox HopLimit;

    QString format() override
    {
        QString format = IPV6_FORMAT;
        //        if (srcMac.text() != "")
        //            format += "src=" + srcMac.text();
        //        if (dstMac.text() != "")
        //            format += ", dst=" + dstMac.text();
        format += ")";

        return format;
    }

    CIPv6fields(QVBoxLayout *parentFrame);
    ~CIPv6fields(){}
};

#endif // CIPV6FIELDS_H


