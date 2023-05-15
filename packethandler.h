#ifndef CPACKETHANDLER_H
#define CPACKETHANDLER_H

#include "protoFields/cfields.h"

class CPacketHandler
{
public:
    CPacketHandler();
    QString formatProtos();
    int sendPacket(QString filename);

    QList<CFields *> protoVector;
    QString Ifc;
    int packetCount;
    int period;
};

#endif // CPACKETHANDLER_H
