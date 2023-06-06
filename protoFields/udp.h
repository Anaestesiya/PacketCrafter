#ifndef CUDP_H
#define CUDP_H


#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSpinBox>

#include "cfields.h"

#define UDP_FORMAT "udp=UDP("

class CUDP : public CFields
{
public:
    CUDP(QVBoxLayout *parentFrame);
    QSpinBox srcPort;
    QSpinBox dstPort;

    QString format() override
    {
        QString format = UDP_FORMAT;
        if (srcPort.value())
            format += "sport=" + QString::number(srcPort.value());
        if (dstPort.value())
            format += ", dport=" + QString::number(dstPort.value());
        format += ")";

        return format;
    }
};

#endif // CUDP_H
