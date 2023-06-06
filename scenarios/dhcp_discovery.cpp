#include "dhcp_discovery.h"

#include <QGridLayout>

DHCP_Discovery::DHCP_Discovery(QVBoxLayout * parentFrame, QPushButton *srcButton) :
    Scenario(),
    CUDP(parentFrame),
    CDHCP(parentFrame)
{
    this->image.load(":/images/DHCP-Discovery.svg.png");
    this->srcButton = srcButton;

    QGridLayout * grd = new QGridLayout();
    scenarioGrpbox.setLayout(grd);
    grd->addWidget(&this->CUDP::grpbox);
    grd->addWidget(&this->CDHCP::grpbox);

    // Add dynamic text translation ?
    // Add size policy

//    grd->addWidget(new QLabel("Source MAC address:"), 0, 0, Qt::AlignLeft);
//    grd->addWidget(&srcMac, 0, 1, Qt::AlignLeft);
//    grd->addWidget(new QLabel("Destination MAC address:"), 1, 0, Qt::AlignLeft);
//    grd->addWidget(&dstMac, 1, 1, Qt::AlignLeft);
    scenarioGrpbox.setTitle("DHCP Discovery");

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

DHCP_Discovery::~DHCP_Discovery()
{
    scenarioGrpbox.layout()->removeWidget(&this->CUDP::grpbox);
    scenarioGrpbox.layout()->removeWidget(&this->CDHCP::grpbox);
    delete scenarioGrpbox.layout();
}
