#ifndef PACKETSAVER_H
#define PACKETSAVER_H

#include "packethandler.h"



class PacketSaver
{
public:
    PacketSaver();
    static void savePacket(CPacketHandler &packetHandler);
};

#endif // PACKETSAVER_H
