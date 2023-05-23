#include "packetvalidator.h"
#include "clogger.h"
#include "CProtocol.h"
#include "packethandler.h"

PacketValidator::PacketValidator()
{

}
void PacketValidator::validateParams(CPacketHandler & packetHandler, QVBoxLayout *verticalLayout_packet)
{
    LOG_DEBUG("In %s", __FUNCTION__);
    packetHandler.protoVector.clear();
    for (int i = 1; i < verticalLayout_packet->count(); ++i)
    {
        QWidget *itemSort = verticalLayout_packet->itemAt(i)->widget();
        packetHandler.protoVector.append(((CProtocol *)itemSort)->fields);
    }
    std::reverse(packetHandler.protoVector.begin(), packetHandler.protoVector.end());
}

int PacketValidator::validateIfc(CPacketHandler &packetHandler, QLineEdit *lineEdit_Ifc)
{
    QRegularExpression emptyRegex("^\\s*$"); // Regular expression to check for empty input
    QPalette palette = lineEdit_Ifc->palette();
    if (lineEdit_Ifc->text().isEmpty() || lineEdit_Ifc->text().contains(emptyRegex)) {
        // Input is empty or contains only whitespace characters
        palette.setColor(QPalette::Base, Qt::red); // Set the background color to red
        lineEdit_Ifc->setPalette(palette);
        LOG_WARNING("Interface field is incorrect");
        return -1;
    } else {
        // Input is not empty
        LOG_DEBUG("Interface is OK");
        palette.setColor(QPalette::Base, Qt::white); // Set the background color to white
    }
    lineEdit_Ifc->setPalette(palette);
    return 0;
}
