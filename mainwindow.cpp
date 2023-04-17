#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    translator.load("PacketCrafter_uk_UA");
    qApp->installTranslator(&translator);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_set_UA_clicked()
{
    qDebug() << "UA" << "\n";
    // toggle effect
    ui->pushButton_set_UA->setEnabled(false);
    ui->pushButton_set_EN->setEnabled(true);
    // ToDo: set translation

    translator.load("PacketCrafter_uk_UA");
    qApp->installTranslator(&translator);

    ui->retranslateUi(this);
}


void MainWindow::on_pushButton_set_EN_clicked()
{
    qDebug() << "EN" << "\n";

    // toggle effect
    ui->pushButton_set_EN->setEnabled(false);
    ui->pushButton_set_UA->setEnabled(true);
    // ToDo: set translation
    translator.load("PacketCrafter_en_US");
    qApp->installTranslator(&translator);

    ui->retranslateUi(this);
}

