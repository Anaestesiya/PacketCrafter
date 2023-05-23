#ifndef PACKETVALIDATOR_H
#define PACKETVALIDATOR_H

#include "packethandler.h"
#include <QLineEdit>
#include <QVBoxLayout>



class PacketValidator
{
public:
    PacketValidator();
    static void validateParams(CPacketHandler & packetHandler, QVBoxLayout *verticalLayout_packet);
    static int validateIfc(CPacketHandler & packetHandler, QLineEdit *IfcLine);
};

#endif // PACKETVALIDATOR_H
