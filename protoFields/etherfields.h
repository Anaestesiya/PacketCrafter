#ifndef CETHERFIELDS_H
#define CETHERFIELDS_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

#include "cfields.h"

#define ETHER_FORMAT "Ethernet=Ether("
// src='%s', dst='%s', type=%d
class CEtherFields : public CFields
{
public:
    QLineEdit srcMac;
    QLineEdit dstMac;

    CEtherFields(QVBoxLayout *parentFrame);
    QString format() override
    {
        QString format = ETHER_FORMAT;
        if (srcMac.text() != "")
            format += "src='" + srcMac.text() + "'";
        if (dstMac.text() != "")
            format += ", dst='" + dstMac.text() + "'";
        format += ")";

        return format;
    }
    ~CEtherFields(){}
    static QString name;
};

#endif // CETHERFIELDS_H
