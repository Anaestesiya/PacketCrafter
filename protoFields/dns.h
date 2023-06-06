#ifndef CDNS_H
#define CDNS_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QComboBox>
#include <QStringList>

#include "cfields.h"

#define DNS_FORMAT "DNS=DNS(qd=DNSQR(qname='" // DNS(qd=DNSQR(qname=domain, qtype=qtype))

class CDNS : public CFields
{
public:
    CDNS(QVBoxLayout *parentFrame);
    QLineEdit dnsServer;
    QLineEdit domain;
    QComboBox qtype;

    QRegularExpression ipv4AddressRegex;

    static QHash<QString, int> *qtypes;

    static void fillTypes()
    {
        qtypes->insert("A", 0);
        qtypes->insert("AAAA", 3);
        qtypes->insert("CNAME", 4);
        qtypes->insert("TXT", 5);
        qtypes->insert("SRV", 8);
        qtypes->insert("SOA", 9);
        qtypes->insert("MX", 11);
    }

    QString format() override
    {

        QString format = DNS_FORMAT;
        format += domain.text();
        format += "', qtype='";
        format += qtype.currentText();
        format += "'))";

        return format;
    }
};


#endif // CICMP_H
