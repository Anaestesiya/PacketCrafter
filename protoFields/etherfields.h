#ifndef CETHERFIELDS_H
#define CETHERFIELDS_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

#define ETHER_FORMAT "ether=Ether(src='%s', dst='%s', type=%d)"

class CEtherFields
{
public:
    QLineEdit src;
    QLineEdit dst;

    QGroupBox grpbox;

    CEtherFields(QVBoxLayout *parentFrame);
    ~CEtherFields(){}
};

#endif // CETHERFIELDS_H
