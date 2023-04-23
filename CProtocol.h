#ifndef CPROTOCOL_H
#define CPROTOCOL_H

#include <QPushButton>
#include <QGroupBox>

typedef enum ELayer
{
    PHYSICAL = 5,
    LINK = 4,
    INTERNET = 3,
    TRANSPORT = 2,
    APPLICATION = 1
} Elayer;

class CProtocol : public QPushButton
{
public:
    CProtocol(QGroupBox *);
    CProtocol();

    Elayer layer;
    // TODO: add Scapy reference

};

#endif // CPROTOCOL_H
