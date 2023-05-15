#ifndef CICMP_H
#define CICMP_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QComboBox>
#include <QStringList>

#include "cfields.h"

#define ICMP_FORMAT "icmp=ICMP("

class Cicmp : public CFields
{
public:
    QComboBox type;
    Cicmp(QVBoxLayout *parentFrame);

    static QHash<QString, int> *icmptypes;

    static void fillTypes()
    {
        icmptypes->insert("echo-reply", 0);
        icmptypes->insert("dest-unreach", 3);
        icmptypes->insert("source-quench", 4);
        icmptypes->insert("redirect", 5);
        icmptypes->insert("echo-request", 8);
        icmptypes->insert("router-advertisement", 9);
        icmptypes->insert("router-solicitation", 10);
        icmptypes->insert("time-exceeded", 11);
        icmptypes->insert("parameter-problem", 12);
        icmptypes->insert("information-request", 15);
        icmptypes->insert("information-response", 16);
        icmptypes->insert("address-mask-request", 17);
        icmptypes->insert("address-mask-reply", 18);
        icmptypes->insert("traceroute", 30);
    }
    QString format() override
    {
        QString format = ICMP_FORMAT;

        format += "type='" + type.currentText() + "'";
        format += ")";

        return format;
    }
};


#endif // CICMP_H
