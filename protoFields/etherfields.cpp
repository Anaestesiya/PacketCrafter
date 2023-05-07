#include "etherfields.h"

#include <QSizePolicy>

// How to fill with default values ?

CEtherFields::CEtherFields(QVBoxLayout *parentFrame) : CFields()
{
    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    // Add dynamic text translation ?
    // Add size policy

    grd->addWidget(new QLabel("Source MAC address:"), 0, 0, Qt::AlignLeft);
    grd->addWidget(&srcMac, 0, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Destination MAC address:"), 1, 0, Qt::AlignLeft);
    grd->addWidget(&dstMac, 1, 1, Qt::AlignLeft);
    grpbox.setTitle("Ethernet");

    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
