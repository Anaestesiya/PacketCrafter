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
    QLineEdit src;
    QLineEdit dst;

    CEtherFields(QVBoxLayout *parentFrame);
    virtual ~CEtherFields(){}

    virtual void format(){}
};

#endif // CETHERFIELDS_H
