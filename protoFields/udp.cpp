#include "udp.h"

CUDP::CUDP(QVBoxLayout *parentFrame) : CFields()
{
    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    srcPort.setButtonSymbols(QAbstractSpinBox::NoButtons);
    dstPort.setButtonSymbols(QAbstractSpinBox::NoButtons);
    srcPort.setRange(1, 65535);
    dstPort.setRange(1, 65535);
    grd->addWidget(new QLabel("Source Port:"), 0, 0, Qt::AlignLeft);
    grd->addWidget(&srcPort, 0, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Destination Port:"), 1, 0, Qt::AlignLeft);
    grd->addWidget(&dstPort, 1, 1, Qt::AlignLeft);

    grpbox.show();
    grpbox.setTitle("UDP");

    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
