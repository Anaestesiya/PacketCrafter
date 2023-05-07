#ifndef CTCP_H
#define CTCP_H

#include <QString>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>

#include "cfields.h"

#define TCP_FORMAT "tcp=TCP()"

class CTCP : public CFields
{
public:
    QSpinBox srcPort;
    QSpinBox dstPort;

    CTCP(QVBoxLayout *parentFrame);
};

#endif // CTCP_H
