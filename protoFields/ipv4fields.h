#ifndef IPV4FIELDS_H
#define IPV4FIELDS_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>

#include "cfields.h"

#define IPV4_FORMAT "ip=IP(src='%s', dst='%s', ttl=%d)"

class CIpv4fields : public CFields
{
public:
    QLineEdit srcIP;
    QLineEdit dstIP;
    QSpinBox TTL;

    CIpv4fields(QVBoxLayout *parentFrame);
    ~CIpv4fields(){}
};

#endif // IPV4FIELDS_H
