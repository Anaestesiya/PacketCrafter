#ifndef TCP_HANDSHAKE_H
#define TCP_HANDSHAKE_H

#include "scenarios/scenario.h"

#include <QVBoxLayout>

#include <protoFields/ipv4fields.h>
#include <protoFields/tcp.h>

class TCP_handshake : public Scenario, CTCP, CIpv4fields
{
public:

    TCP_handshake(QVBoxLayout * parentFrame, QPushButton *srcButton);

    void startScenario() override
    {

    }
    ~TCP_handshake();
};

#endif // TCP_HANDSHAKE_H
