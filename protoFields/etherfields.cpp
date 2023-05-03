#include "etherfields.h"

#include <QSizePolicy>

// How to fill with default values ?

CEtherFields::CEtherFields(QVBoxLayout *parentFrame) : CFields()
{
    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    // Add CSS ?

    grd->addWidget(new QLabel("Source MAC address:"), 0, 0, Qt::AlignLeft);
    grd->addWidget(&src, 0, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Destination MAC address:"), 1, 0, Qt::AlignLeft);
    grd->addWidget(&dst, 1, 1, Qt::AlignLeft);
    grpbox.setTitle("Ethernet");

    parentFrame->insertWidget(0, &grpbox);
    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
