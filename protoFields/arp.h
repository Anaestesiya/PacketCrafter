#ifndef CARP_H
#define CARP_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>

#include "cfields.h"

#define ARP_FORMAT "arp=ARP()"

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
    QLineEdit hwsrc;
    QLineEdit hwdst;
    QLineEdit ipsrc;
    QLineEdit ipdst;

    CARP(QVBoxLayout *parent);
};

#endif // CARP_H
