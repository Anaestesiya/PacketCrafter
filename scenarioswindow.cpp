#include "scenarioswindow.h"
#include "ui_scenarioswindow.h"

#include "scenarios/tcp_handshake.h"
#include "scenarios/scenario.h"

ScenariosWindow::ScenariosWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScenariosWindow)
{
    ui->setupUi(this);
    activeScenario = nullptr;
}

ScenariosWindow::~ScenariosWindow()
{
    delete ui;
}

void ScenariosWindow::on_pushButton_clicked()
{
    this->hide();
    m->show();
}

void ScenariosWindow::showScenario(Scenario *scenario)
{
    this->activeScenario = scenario;
    // Set the image to the QLabel
    ui->label_scenario->setPixmap(scenario->image);
    // Set the size policies for the QLabel
    ui->label_scenario->setScaledContents(true);
    ui->label_scenario->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_scenario->setAlignment(Qt::AlignCenter);
    ui->verticalLayout_fields->insertWidget(0, &scenario->scenarioGrpbox);
}

void ScenariosWindow::hideScenario(Scenario *scenario)
{
    ui->label_scenario->clear();
    // Set the size policies for the QLabel
    scenario->scenarioGrpbox.hide();
    ui->verticalLayout_fields->removeWidget(&scenario->scenarioGrpbox);
    delete scenario;
    activeScenario = nullptr;
}

void ScenariosWindow::on_pushButton_5_clicked()
{
    if (activeScenario != nullptr)
    {
        QPushButton *tmp = activeScenario->srcButton;
        hideScenario(activeScenario);
        if (tmp == ui->pushButton_5)
            return;
    }

    showScenario(new TCP_handshake(ui->verticalLayout_fields, ui->pushButton_5));
}

