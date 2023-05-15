#ifndef CHTTP_H
#define CHTTP_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

#include "cfields.h"

#define HTTP_FORMAT "http=HTTP()/HTTPRequest(Method='%s', Path='%s', Http_Version='%s', Host='%s', Accept='%s', Cache_Control='%s')"

class Chttp : public CFields
{
public:
    QLineEdit method;
    QLineEdit path;
    QLineEdit version;
    QLineEdit host;
    QLineEdit accept;
    QLineEdit cacheControl;

    QString format() override
    {
        QString format = HTTP_FORMAT;
//        if (srcMac.text() != "")
//            format += "src=" + srcMac.text();
//        if (dstMac.text() != "")
//            format += ", dst=" + dstMac.text();
        format += ")";

        return format;
    }

    Chttp(QVBoxLayout *parentFrame);
};

#endif // CHTTP_H
