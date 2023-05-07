#ifndef CETHERFIELDS_H
#define CETHERFIELDS_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

#include "cfields.h"

#define ETHER_FORMAT "ether=Ether(src='%s', dst='%s', type=%d)"

class CEtherFields : public CFields
{
public:
    QLineEdit srcMac;
    QLineEdit dstMac;

    CEtherFields(QVBoxLayout *parentFrame);
    ~CEtherFields(){}
};

#endif // CETHERFIELDS_H
