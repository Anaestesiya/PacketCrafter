#ifndef CFIELDS_H
#define CFIELDS_H

#include <QGroupBox>

class CFields
{
public:
    CFields();
    QGroupBox grpbox;
    virtual QString format() = 0;
    virtual ~CFields(){}
};

#endif // CFIELDS_H
