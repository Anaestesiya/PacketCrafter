#ifndef CTCP_H
#define CTCP_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>

#include "cfields.h"

#define TCP_FORMAT "TCP=TCP("

class CTCP : public CFields
{
public:
    QSpinBox srcPort;
    QSpinBox dstPort;

    QString format() override
    {
        QString format = TCP_FORMAT;
        if (srcPort.value())
            format += "sport=" + srcPort.value();
        if (dstPort.value())
            format += ", dport=" + dstPort.value();
        format += ")";

        return format;
    }

    CTCP(QVBoxLayout *parentFrame);
    static QString name;
};

#endif // CTCP_H
