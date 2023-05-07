#include "udp.h"

CUDP::CUDP(QVBoxLayout *parentFrame) : CFields()
{
    QGridLayout * grd = new QGridLayout();
    grpbox.setLayout(grd);

    // Add dynamic text translation ?
    // Add size policy

    grpbox.setTitle("UDP");

    parentFrame->setAlignment(Qt::AlignCenter);
    grpbox.show();
}
