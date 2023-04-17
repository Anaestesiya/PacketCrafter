#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_set_UA_clicked()
{
    // toggle effect
    ui->pushButton_set_UA->setEnabled(false);
    ui->pushButton_set_EN->setEnabled(true);
    // ToDo: set translation
}


void MainWindow::on_pushButton_set_EN_clicked()
{
    // toggle effect
    ui->pushButton_set_EN->setEnabled(false);
    ui->pushButton_set_UA->setEnabled(true);
    // ToDo: set translation
}

