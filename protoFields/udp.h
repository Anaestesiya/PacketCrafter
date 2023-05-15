#ifndef CUDP_H
#define CUDP_H


#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

#include "cfields.h"

#define UDP_FORMAT "udp=UDP()"

class CUDP : public CFields
{
public:
    CUDP(QVBoxLayout *parentFrame);

    QString format() override
    {
        QString format = UDP_FORMAT;
//        if (srcMac.text() != "")
//            format += "src=" + srcMac.text();
//        if (dstMac.text() != "")
//            format += ", dst=" + dstMac.text();
        format += ")";

        return format;
    }
};

#endif // CUDP_H
