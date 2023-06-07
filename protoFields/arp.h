#ifndef CARP_H
#define CARP_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>

#include "cfields.h"

#define ARP_FORMAT "ARP=ARP(pdst='"

const QStringList opCodes =
{
    "who-has",
    "is-at",
    "RARP-req",
    "RARP-rep",
    "DRARP-req",
    "DRARP-rep",
    "DRARP-err",
    "InARP-req",
    "InARP-rep"
};

class CARP : public CFields
{
public:
    QComboBox opCode;
//    QLineEdit hwsrc;
//    QLineEdit hwdst;
    QLineEdit ipsrc;
    QLineEdit ipdst;

    QString format() override
    {
        QString format = ARP_FORMAT;
        format += ipdst.text();
        format += "'";
        if (ipsrc.text() != "")
        {
            format += ",psrc='";
            format += ipsrc.text();
            format += "'";
        }
        format += ")";
        return format;
    }

    CARP(QVBoxLayout *parent);
};

#endif // CARP_H
