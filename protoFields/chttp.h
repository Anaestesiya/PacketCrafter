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
        char *format = new char[10000];
        sscanf(format, HTTP_FORMAT, method.text().toStdString().c_str(),
                path.text().toStdString().c_str(), version.text().toStdString().c_str(),
                host.text().toStdString().c_str(), accept.text().toStdString().c_str(),
                cacheControl.text().toStdString().c_str());
        QString str_format(format);
        return str_format;
    }

    Chttp(QVBoxLayout *parentFrame);
};

#endif // CHTTP_H
