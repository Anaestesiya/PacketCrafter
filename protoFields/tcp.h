#ifndef CTCP_H
#define CTCP_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>

#include "cfields.h"

#define TCP_FORMAT "tcp=TCP()"

class CTCP : public CFields
{
public:
    QSpinBox srcPort;
    QSpinBox dstPort;

    QString format() override
    {
        QString format = TCP_FORMAT;
        //        if (srcMac.text() != "")
        //            format += "src=" + srcMac.text();
        //        if (dstMac.text() != "")
        //            format += ", dst=" + dstMac.text();
        format += ")";

        return format;
    }

    CTCP(QVBoxLayout *parentFrame);
};

#endif // CTCP_H
