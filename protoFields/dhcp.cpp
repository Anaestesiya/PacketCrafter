#include "dhcp.h"
QHash<QString, int> *CDHCP::dhcptypes = new QHash<QString, int>();

CDHCP::CDHCP(QVBoxLayout *parentFrame) : CFields(),
    ipv4AddressRegex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$")
{

    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    // Add dynamic text translation ?
    // Add size policy

    fillTypes();
    type.addItems(QStringList(CDHCP::dhcptypes->keys()));
    type.setCurrentText("discovery");
    grd->addWidget(new QLabel("Packet type:"), 0, 0, Qt::AlignLeft);
    grd->addWidget(&type, 0, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("New IPv4:"), 1, 0, Qt::AlignLeft);
    grd->addWidget(&newIP, 1, 1, Qt::AlignLeft);

    QValidator *IPvalidator = new QRegularExpressionValidator(ipv4AddressRegex);
    newIP.setValidator(IPvalidator);

    grpbox.setTitle("DHCP");

    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
