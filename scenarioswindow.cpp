#include "scenarioswindow.h"
#include "clogger.h"
#include "languagecontroller.h"
#include "ui_scenarioswindow.h"

#include "scenarios/tcp_handshake.h"
#include "scenarios/scenario.h"

ScenariosWindow::ScenariosWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScenariosWindow)
{
    ui->setupUi(this);
    activeScenario = nullptr;
    ui->pushButton_EN->setEnabled(false);
}

ScenariosWindow::~ScenariosWindow()
{
    delete ui;
}

void ScenariosWindow::on_pushButton_clicked()
{
    this->hide();
    m->show();
    m->changeLanguage();
}

void ScenariosWindow::changeLanguage()
{
    if (ui->pushButton_UA->isEnabled() && LanguageController::currentLanguage == LanguageController::UA)
    {
        ui->pushButton_UA->setEnabled(false);
        ui->pushButton_EN->setEnabled(true);

        LanguageController::changeToUA();
    }
    if (ui->pushButton_EN->isEnabled() && LanguageController::currentLanguage == LanguageController::EN)
    {
        ui->pushButton_UA->setEnabled(true);
        ui->pushButton_EN->setEnabled(false);

        LanguageController::changeToEN();
    }
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


void ScenariosWindow::on_pushButton_4_clicked()
{
    QRegularExpression emptyRegex("^\\s*$"); // Regular expression to check for empty input
    QPalette palette = ui->lineEdit->palette();
    if (ui->lineEdit->text().isEmpty() || ui->lineEdit->text().contains(emptyRegex)) {
        // Input is empty or contains only whitespace characters
        palette.setColor(QPalette::Base, Qt::red); // Set the background color to red
        ui->lineEdit->setPalette(palette);
        return;
    } else {
        // Input is not empty
        palette.setColor(QPalette::Base, Qt::white); // Set the background color to white
    }
    ui->lineEdit->setPalette(palette);

    activeScenario->startScenario(ui->lineEdit->text());
}


void ScenariosWindow::on_pushButton_UA_clicked()
{
    LOG_INFO("Change language to UA");

    // toggle effect
    LanguageController::currentLanguage = LanguageController::UA;
    changeLanguage();

    ui->retranslateUi(this);
}

void ScenariosWindow::on_pushButton_EN_clicked()
{
    LOG_INFO("Change language to EN");

    // toggle effect
    LanguageController::currentLanguage = LanguageController::EN;
    changeLanguage();

    ui->retranslateUi(this);
}

