#include "tcp_handshake.h"

#include <QGridLayout>

TCP_handshake::TCP_handshake(QVBoxLayout * parentFrame, QPushButton *srcButton) :
    Scenario(),
    CTCP(parentFrame),
    CIpv4fields(parentFrame)
{
    this->image.load(":/images/Tcp-handshake.svg.png");
    this->srcButton = srcButton;

    QGridLayout * grd = new QGridLayout();
    scenarioGrpbox.setLayout(grd);
    grd->addWidget(&this->CTCP::grpbox);
    grd->addWidget(&this->CIpv4fields::grpbox);

    // Add dynamic text translation ?
    // Add size policy

//    grd->addWidget(new QLabel("Source MAC address:"), 0, 0, Qt::AlignLeft);
//    grd->addWidget(&srcMac, 0, 1, Qt::AlignLeft);
//    grd->addWidget(new QLabel("Destination MAC address:"), 1, 0, Qt::AlignLeft);
//    grd->addWidget(&dstMac, 1, 1, Qt::AlignLeft);
    scenarioGrpbox.setTitle("TCP Handhsake");

//    QRegularExpression macAddressRegex("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
//    QValidator *validator = new QRegularExpressionValidator(macAddressRegex);

//    dstMac.setValidator(validator);
//    srcMac.setValidator(validator);
//    dstMac.setPlaceholderText("ff:ff:ff:ff:ff:ff");
//    srcMac.setPlaceholderText("Autofill");

    parentFrame->setAlignment(Qt::AlignCenter);
    qDebug() << "Show scenarioGrpbox";
    scenarioGrpbox.show();
}

TCP_handshake::~TCP_handshake()
{
    scenarioGrpbox.layout()->removeWidget(&this->CTCP::grpbox);
    scenarioGrpbox.layout()->removeWidget(&this->CIpv4fields::grpbox);
    delete scenarioGrpbox.layout();
}
