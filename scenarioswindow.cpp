#include "scenarioswindow.h"
#include "ui_scenarioswindow.h"

ScenariosWindow::ScenariosWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScenariosWindow)
{
    ui->setupUi(this);
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

