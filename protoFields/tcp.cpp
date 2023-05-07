#include "tcp.h"

CTCP::CTCP(QVBoxLayout *parentFrame) : CFields()
{
    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    // Add dynamic text translation ?
    // Add size policy

    srcPort.setButtonSymbols(QAbstractSpinBox::NoButtons);
    dstPort.setButtonSymbols(QAbstractSpinBox::NoButtons);
    srcPort.setRange(1, 65535);
    dstPort.setRange(1, 65535);
    grd->addWidget(new QLabel("Source Port:"), 0, 0, Qt::AlignLeft);
    grd->addWidget(&srcPort, 0, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Destination Port:"), 1, 0, Qt::AlignLeft);
    grd->addWidget(&dstPort, 1, 1, Qt::AlignLeft);
    grpbox.setTitle("TCP");

    parentFrame->insertWidget(0, &grpbox);
    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
