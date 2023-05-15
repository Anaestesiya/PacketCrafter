#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDialog>

#include "protoFields/etherfields.h"
#include "protoFields/ipv4fields.h"
#include "protoFields/ipv6fields.h"
#include "protoFields/chttp.h"
#include "protoFields/icmp.h"
#include "protoFields/tcp.h"
#include "protoFields/udp.h"
#include "protoFields/arp.h"

#include <QComboBox>

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
            // Let ICMP be as TCP layer
            if (!static_cast<CProtocol *>(grp->itemAt(k)->widget())->text().startsWith("ICMP"))
                static_cast<CProtocol *>(grp->itemAt(k)->widget())->layer = (ELayer)(i);
            else static_cast<CProtocol *>(grp->itemAt(k)->widget())->layer = (ELayer)(i-1);
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

void MainWindow::addProtoAction(CProtocol *proto, CFields *fields)
{
    // Init widget
    CProtocol *packetproto = new CProtocol();
    packetproto->fields = fields;
    packetproto->setGeometry(proto->geometry());
    packetproto->setText(proto->text());
    packetproto->layer = proto->layer;
    packetproto->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    packetproto->setMinimumHeight(75);
    connect(packetproto, SIGNAL(clicked()),this, SLOT(clickedPacketProto()));


    // Filter alogorithm
    QGridLayout *grp = (QGridLayout *)proto->parentWidget()->layout();

    if (proto->parentWidget() != ui->groupBox_internet)
    {
        for (int i = 0; i < grp->count(); ++i)
        {
            static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(false);
        }
    }
    else
    {
        for (int i = 0; i < grp->count(); ++i)
        {
            if (proto->text().contains("v6") && !static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().contains("v6"))
            {
                static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(false);
            }
            else if (!proto->text().contains("v6") && static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().contains("v6"))
            {
                static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(false);
            }
            proto->setEnabled(false);
        }
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
    if (packetproto->fields)
        ui->verticalLayout_fields->insertWidget(index - 1, &packetproto->fields->grpbox);
    ui->verticalLayout_packet->setAlignment(Qt::AlignCenter);

    packetproto->show();

    // Init custom fileds layout

}

// Remove widget from Packet layout when clicked
void MainWindow::clickedPacketProto()
{
    qDebug() << ((CProtocol *)sender())->layer;
    QGridLayout *grp = layer_groups[((CProtocol *)sender())->layer - 1];
    if (((CProtocol *)sender())->text().contains("ICMP"))
        grp = layer_groups[((CProtocol *)sender())->layer];
    for (int i = 0; i < grp->count(); ++i)
    {
        static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(true);
    }

    ((CProtocol*)sender())->hide();
    ui->verticalLayout_packet->removeWidget((CProtocol*)sender());

    if (((CProtocol *)sender())->fields != nullptr)
    {
        ((CProtocol *)sender())->fields->grpbox.hide();
        ui->verticalLayout_fields->removeWidget(&((CProtocol *)sender())->fields->grpbox);
        delete ((CProtocol *)sender())->fields;
    }
    delete sender();
}

// Ethernet
void MainWindow::on_pushButton_14_clicked()
{
    addProtoAction(ui->pushButton_14, new CEtherFields(ui->verticalLayout_fields));
}

// PPP
void MainWindow::on_pushButton_13_clicked()
{
    addProtoAction(ui->pushButton_13);
}

// ARP
void MainWindow::on_pushButton_11_clicked()
{
    addProtoAction(ui->pushButton_11, new CARP(ui->verticalLayout_fields));
}

// IPv4
void MainWindow::on_pushButton_10_clicked()
{
    addProtoAction(ui->pushButton_10, new CIpv4fields(ui->verticalLayout_fields));
}

// IPv6
void MainWindow::on_pushButton_15_clicked()
{
    addProtoAction(ui->pushButton_15, new CIPv6fields(ui->verticalLayout_fields));
}

// ICMP
void MainWindow::on_pushButton_12_clicked()
{
    addProtoAction(ui->pushButton_12, new Cicmp(ui->verticalLayout_fields));
}

// ICMPv6
void MainWindow::on_pushButton_16_clicked()
{
    addProtoAction(ui->pushButton_16);
}


// TCP
void MainWindow::on_pushButton_8_clicked()
{
    addProtoAction(ui->pushButton_8, new CTCP(ui->verticalLayout_fields));
}

// UDP
void MainWindow::on_pushButton_9_clicked()
{
    addProtoAction(ui->pushButton_9, new CUDP(ui->verticalLayout_fields));
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
    addProtoAction(ui->pushButton_5, new Chttp(ui->verticalLayout_fields));
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

// send button
void MainWindow::on_pushButton_2_clicked()
{
    QProcess process;

    process.start("/home/anastasiiafrolova/send_ssdp.py");
    process.waitForFinished();

    QString output(process.readAllStandardOutput());
    qDebug()<<output;

    QString err(process.readAllStandardError());
    qDebug()<<err;
}

// TODOs

// 1. add "Autofill strings to lineedits as a hint"
// 2. add default values to particular fields
// 3. Send packet dialog
// 4. Varify packet
// 5. Open and parse file
// 6. Auto open wireshark to look for traffic ?

