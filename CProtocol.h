#ifndef CPROTOCOL_H
#define CPROTOCOL_H

#include <QPushButton>
#include <QGroupBox>

typedef enum ELayer
{
    PHYSICAL = 0,
    LINK,
    INTERNET,
    TRANSPORT,
    APPLICATION
} Elayer;

class CProtocol : public QPushButton
{
public:
    CProtocol(QGroupBox *);
    CProtocol();
private:
    Elayer layer;
    // TODO: add Scapy reference

};

#endif // CPROTOCOL_H
