#include "dns.h"
QHash<QString, int> *CDNS::qtypes = new QHash<QString, int>();

CDNS::CDNS(QVBoxLayout *parentFrame) : CFields(),
    ipv4AddressRegex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$")
{

    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    // Add dynamic text translation ?
    // Add size policy

    fillTypes();
    qtype.addItems(QStringList(CDNS::qtypes->keys()));
    qtype.setCurrentText("A");
//    grd->addWidget(new QLabel("Nameserver:"), 0, 0, Qt::AlignLeft);
//    grd->addWidget(&dnsServer, 0, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Domain:"), 0, 0, Qt::AlignLeft);
    grd->addWidget(&domain, 0, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Query type:"), 1, 0, Qt::AlignLeft);
    grd->addWidget(&qtype, 1, 1, Qt::AlignLeft);

//    QValidator *IPvalidator = new QRegularExpressionValidator(ipv4AddressRegex);
//    dnsServer.setValidator(IPvalidator);

    grpbox.setTitle("DNS");

    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
