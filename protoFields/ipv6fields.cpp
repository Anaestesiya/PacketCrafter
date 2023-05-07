
#include "ipv6fields.h"

CIPv6fields::CIPv6fields(QVBoxLayout *parentFrame) : CFields()
{
    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    // Add dynamic text translation ?
    // Add size policy
    HopLimit.setButtonSymbols(QAbstractSpinBox::NoButtons);
    HopLimit.setRange(1, 255);
    grd->addWidget(new QLabel("Source IP address:"), 0, 0, Qt::AlignLeft);
    grd->addWidget(&srcIP, 0, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Destination IP address:"), 1, 0, Qt::AlignLeft);
    grd->addWidget(&dstIP, 1, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Hop Limit:"), 2, 0, Qt::AlignLeft);
    grd->addWidget(&HopLimit, 2, 1, Qt::AlignLeft);
    grpbox.setTitle("IPv6");

    parentFrame->insertWidget(0, &grpbox);
    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
