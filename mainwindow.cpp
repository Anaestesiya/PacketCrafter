#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRect>
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    translator.load("PacketCrafter_uk_UA");
    qApp->installTranslator(&translator);

    layer_groups[0] = (QGridLayout *)(ui->groupBox_application->layout());
    layer_groups[1] = (QGridLayout *)(ui->groupBox_transport->layout());
    layer_groups[2] = (QGridLayout *)(ui->groupBox_internet->layout());
    layer_groups[3] = (QGridLayout *)(ui->groupBox_link->layout());
    layer_groups[4] = (QGridLayout *)(ui->groupBox_physical->layout());

    // fill protos

    for (int i = APPLICATION; i <= PHYSICAL; i++) {
        QGridLayout *grp = layer_groups[i - 1];
        for (int k = 0; k < grp->count(); ++k)
        {
            static_cast<CProtocol *>(grp->itemAt(k)->widget())->layer = (ELayer)(i);
        }
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

    int index = 1;
    for (int i = 1; i < ui->verticalLayout_packet->count(); ++i)
    {
        index = i;
        QWidget *itemSort = ui->verticalLayout_packet->itemAt(i)->widget();
        qDebug() << packetproto->layer << " " << ((CProtocol *)itemSort)->layer;
        if (packetproto->layer < ((CProtocol *)itemSort)->layer)
            break;
        else index = index + 1;
    }

    ui->verticalLayout_packet->insertWidget(index, packetproto);
    ui->verticalLayout_packet->setAlignment(Qt::AlignCenter);

    packetproto->show();
}

void MainWindow::clickedPacketProto()
{
    qDebug() << ((CProtocol *)sender())->layer;
    QGridLayout *grp = layer_groups[((CProtocol *)sender())->layer - 1];
    for (int i = 0; i < grp->count(); ++i)
    {
        static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(true);
    }

    ((CProtocol*)sender())->hide();
    ui->verticalLayout_packet->removeWidget((CProtocol*)sender());
    delete sender();
}

// Ethernet
void MainWindow::on_pushButton_14_clicked()
{
    addProtoAction(ui->pushButton_14);
}

// PPP
void MainWindow::on_pushButton_13_clicked()
{
    addProtoAction(ui->pushButton_13);
}

// ARP
void MainWindow::on_pushButton_11_clicked()
{
    addProtoAction(ui->pushButton_11);
}

// IPv4
void MainWindow::on_pushButton_10_clicked()
{
    addProtoAction(ui->pushButton_10);
}

// IPv6
void MainWindow::on_pushButton_15_clicked()
{
    addProtoAction(ui->pushButton_15);
}

// ICMP
void MainWindow::on_pushButton_12_clicked()
{
    addProtoAction(ui->pushButton_12);
}

// ICMPv6
void MainWindow::on_pushButton_16_clicked()
{
    addProtoAction(ui->pushButton_16);
}


// TCP
void MainWindow::on_pushButton_8_clicked()
{
    addProtoAction(ui->pushButton_8);
}

// UDP
void MainWindow::on_pushButton_9_clicked()
{
    addProtoAction(ui->pushButton_9);
}

/*
 *     QProcess process;
    process.start("/home/anastasiiafrolova/send_ssdp.py");
    process.waitForFinished();

    QString output(process.readAllStandardOutput());
    qDebug()<<output;

    QString err(process.readAllStandardError());
    qDebug()<<err;
*/

// HTTP
void MainWindow::on_pushButton_5_clicked()
{
    addProtoAction(ui->pushButton_5);
}

// FTP
void MainWindow::on_pushButton_7_clicked()
{
    addProtoAction(ui->pushButton_7);
}

// DNS
void MainWindow::on_pushButton_6_clicked()
{
    addProtoAction(ui->pushButton_6);
}

// DHCP
void MainWindow::on_pushButton_17_clicked()
{
    addProtoAction(ui->pushButton_17);
}

