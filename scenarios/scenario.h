#ifndef SCENARIO_H
#define SCENARIO_H

#include <QGroupBox>
#include <QPushButton>



class Scenario
{
public:
    QPixmap image;
    QGroupBox scenarioGrpbox;
    QPushButton *srcButton;

    Scenario();

    virtual int startScenario(QString Ifc) = 0;

    virtual ~Scenario(){}
};

#endif // SCENARIO_H
