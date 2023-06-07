#include "arp.h"

CARP::CARP(QVBoxLayout *parentFrame) : CFields()
{
    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    // Add dynamic text translation ?
    // Add size policy

    grpbox.setTitle("ARP");
    opCode.insertItems(0, opCodes);
    grd->addWidget(new QLabel("Operation code:"), 0, 0, Qt::AlignLeft);
    grd->addWidget(&opCode, 0, 1, Qt::AlignLeft);
    /*grd->addWidget(new QLabel("Source MAC:"), 1, 0, Qt::AlignLeft);
    grd->addWidget(&hwsrc, 1, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Destination MAC:"), 2, 0, Qt::AlignLeft);
    grd->addWidget(&hwdst, 2, 1, Qt::AlignLeft);*/
    grd->addWidget(new QLabel("Source IP:"), 3, 0, Qt::AlignLeft);
    grd->addWidget(&ipsrc, 3, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Destination IP:"), 4, 0, Qt::AlignLeft);
    grd->addWidget(&ipdst, 4, 1, Qt::AlignLeft);

    /*QRegularExpression macAddressRegex("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
    QValidator *MACvalidator = new QRegularExpressionValidator(macAddressRegex);*/
    QRegularExpression ipv4AddressRegex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QValidator *IPvalidator = new QRegularExpressionValidator(ipv4AddressRegex);

//    hwsrc.setValidator(MACvalidator);
//    hwdst.setValidator(MACvalidator);
    ipsrc.setValidator(IPvalidator);
    ipsrc.setPlaceholderText("Autofill");
    ipdst.setValidator(IPvalidator);

    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
