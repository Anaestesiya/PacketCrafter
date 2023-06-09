#include "icmp.h"

QHash<QString, int> *Cicmp::icmptypes = new QHash<QString, int>();
QString Cicmp::name = "ICMP";
Cicmp::Cicmp(QVBoxLayout *parentFrame) : CFields()
{
    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    // Add dynamic text translation ?
    // Add size policy

    fillTypes();
    type.addItems(QStringList(Cicmp::icmptypes->keys()));
    type.setCurrentText("echo-request");
    grd->addWidget(new QLabel("Packet type:"), 0, 0, Qt::AlignLeft);
    grd->addWidget(&type, 0, 1, Qt::AlignLeft);
    // Add and then remove IPv4 widget also

    grpbox.setTitle("ICMP");

    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
