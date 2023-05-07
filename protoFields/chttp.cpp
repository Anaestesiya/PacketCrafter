#include "chttp.h"

Chttp::Chttp(QVBoxLayout *parentFrame) : CFields()
{
    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    // Add dynamic text translation ?
    // Add size policy

    grpbox.setTitle("HTTP");
    grd->addWidget(new QLabel("Method:"), 0, 0, Qt::AlignLeft);
    grd->addWidget(&method, 0, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Path:"), 0, 2, Qt::AlignLeft);
    grd->addWidget(&path, 0, 3, Qt::AlignLeft);
    grd->addWidget(new QLabel("Ver:"), 0, 4, Qt::AlignLeft);
    grd->addWidget(&version, 0, 5, Qt::AlignLeft);
    grd->addWidget(new QLabel("Host:"), 1, 0, Qt::AlignLeft);
    grd->addWidget(&host, 1, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Accept:"), 2, 0, Qt::AlignLeft);
    grd->addWidget(&accept, 2, 1, Qt::AlignLeft);
    grd->addWidget(new QLabel("Cache:"), 3, 0, Qt::AlignLeft);
    grd->addWidget(&cacheControl, 3, 1, Qt::AlignLeft);

    parentFrame->insertWidget(0, &grpbox);
    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
