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
};

#endif // CUDP_H
