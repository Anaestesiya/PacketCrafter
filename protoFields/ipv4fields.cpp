#include "ipv4fields.h"

CIpv4fields::CIpv4fields(QVBoxLayout *parentFrame) : CFields()
{
    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    // Add dynamic text translation ?
    // Add size policy
    TTL.setButtonSymbols(QAbstractSpinBox::NoButtons);
    TTL.setRange(1, 255);
    grd->addWidget(new QLabel("Source IP address:"), 0, 0, Qt::AlignLeft);
    grd->addWidget(&srcIP, 0, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Destination IP address:"), 1, 0, Qt::AlignLeft);
    grd->addWidget(&dstIP, 1, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Time to live:"), 2, 0, Qt::AlignLeft);
    grd->addWidget(&TTL, 2, 1, Qt::AlignLeft);
    grpbox.setTitle("IPv4");

    QRegularExpression ipv4AddressRegex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QValidator *IPvalidator = new QRegularExpressionValidator(ipv4AddressRegex);

    srcIP.setValidator(IPvalidator);
    dstIP.setValidator(IPvalidator);

    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
