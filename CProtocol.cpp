#include "CProtocol.h"

CProtocol::CProtocol() :
    QPushButton()
{
    fields = nullptr;
}

CProtocol::CProtocol(QGroupBox *box) :
    QPushButton(box)
{
    fields = nullptr;
}
