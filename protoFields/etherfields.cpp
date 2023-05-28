#include "etherfields.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSizePolicy>

// How to fill with default values ?
QString CEtherFields::name = "Ethernet";
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

    QRegularExpression macAddressRegex("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
    QValidator *validator = new QRegularExpressionValidator(macAddressRegex);

    dstMac.setValidator(validator);
    srcMac.setValidator(validator);
    dstMac.setPlaceholderText("ff:ff:ff:ff:ff:ff");
    srcMac.setPlaceholderText("Autofill");

    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
