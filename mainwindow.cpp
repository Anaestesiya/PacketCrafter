#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRect>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    translator.load("PacketCrafter_uk_UA");
    qApp->installTranslator(&translator);

    // fill protos

    QGridLayout *grp = (QGridLayout *)ui->groupBox_application->layout();
    for (int i = 0; i < grp->count(); ++i)
    {
        static_cast<CProtocol *>(grp->itemAt(i)->widget())->layer = APPLICATION;
    }
    grp = (QGridLayout *)ui->groupBox_transport->layout();
    for (int i = 0; i < grp->count(); ++i)
    {
        static_cast<CProtocol *>(grp->itemAt(i)->widget())->layer = TRANSPORT;
    }
    grp = (QGridLayout *)ui->groupBox_internet->layout();
    for (int i = 0; i < grp->count(); ++i)
    {
        static_cast<CProtocol *>(grp->itemAt(i)->widget())->layer = INTERNET;
    }
    grp = (QGridLayout *)ui->groupBox_link->layout();
    for (int i = 0; i < grp->count(); ++i)
    {
        static_cast<CProtocol *>(grp->itemAt(i)->widget())->layer = LINK;
    }
    grp = (QGridLayout *)ui->groupBox_physical->layout();
    for (int i = 0; i < grp->count(); ++i)
    {
        static_cast<CProtocol *>(grp->itemAt(i)->widget())->layer = PHYSICAL;
    }
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

void MainWindow::addProtoAction(CProtocol *proto)
{
    CProtocol *packetproto = new CProtocol();
    packetproto->setGeometry(proto->geometry());
    packetproto->setText(proto->text());
    packetproto->layer = proto->layer;
    packetproto->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    packetproto->setMinimumHeight(75);
    connect(packetproto, SIGNAL(clicked()),this, SLOT(clickedPacketProto()));

    QGridLayout *grp = (QGridLayout *)proto->parentWidget()->layout();

    for (int i = 0; i < grp->count(); ++i)
    {
        static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(false);
    }

    ui->verticalLayout_packet->insertWidget(packetproto->layer > ui->verticalLayout_packet->count() ? ui->verticalLayout_packet->count() : packetproto->layer, packetproto);
    ui->verticalLayout_packet->setAlignment(Qt::AlignCenter);

    packetproto->show();
}

void MainWindow::on_pushButton_13_clicked()
{
    addProtoAction(ui->pushButton_13);
}


void MainWindow::on_pushButton_5_clicked()
{
    addProtoAction(ui->pushButton_5);
}

void MainWindow::clickedPacketProto()
{
    // show packet headers
    QMessageBox msgBox;
    msgBox.setWindowTitle("MessageBox Title");
    msgBox.setText("You Clicked "+ ((QPushButton*)sender())->text());
    msgBox.exec();
}

