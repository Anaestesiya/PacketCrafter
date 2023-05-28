#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDialog>

#include "packethandler.h"
#include "protoFields/etherfields.h"
#include "protoFields/ipv4fields.h"
#include "protoFields/ipv6fields.h"
#include "protoFields/chttp.h"
#include "protoFields/icmp.h"
#include "protoFields/tcp.h"
#include "protoFields/udp.h"
#include "protoFields/arp.h"

#include "savefiledialog.h"
#include "scenarioswindow.h"
#include "clogger.h"
#include "packetsaver.h"
#include "packetvalidator.h"
#include "languagecontroller.h"

#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_set_EN->setEnabled(false);
    ui->pushButton_set_UA->setEnabled(true);
    changeLanguage();

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
    ui->spinBox_count->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_count->setRange(1, 10000);

    ui->spinBox_period->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_period->setRange(1,10);
    LOG_INFO("Init Application successfully");
}

MainWindow::~MainWindow()
{
    LOG_INFO("End App");
    delete ui;
}

void MainWindow::changeLanguage()
{
    if (ui->pushButton_set_UA->isEnabled() && LanguageController::currentLanguage == LanguageController::UA)
    {
        ui->pushButton_set_UA->setEnabled(false);
        ui->pushButton_set_EN->setEnabled(true);

        LanguageController::changeToUA();
    }
    if (ui->pushButton_set_EN->isEnabled() && LanguageController::currentLanguage == LanguageController::EN)
    {
        ui->pushButton_set_UA->setEnabled(true);
        ui->pushButton_set_EN->setEnabled(false);

        LanguageController::changeToEN();
    }

}


void MainWindow::on_pushButton_set_UA_clicked()
{
    LOG_INFO("Change language to UA");

    // toggle effect
    LanguageController::currentLanguage = LanguageController::UA;
    changeLanguage();

    ui->retranslateUi(this);
}


void MainWindow::on_pushButton_set_EN_clicked()
{
    LOG_INFO("Change language to EN");

    // toggle effect
    LanguageController::currentLanguage = LanguageController::EN;
    changeLanguage();

    ui->retranslateUi(this);
}

void MainWindow::addProtoAction(CProtocol *proto, CFields *fields)
{
    LOG_INFO("%s is added", proto->text().toStdString().c_str());
    qDebug() << proto->text().toStdString().c_str();
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
            LOG_INFO("%s is not functional anymore", static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().toStdString().c_str());
        }
    }
    else
    {
        for (int i = 0; i < grp->count(); ++i)
        {
            if (proto->text().contains("v6") && !static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().contains("v6"))
            {
                static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(false);
                LOG_INFO("%s is not functional anymore", static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().toStdString().c_str());
            }
            else if (!proto->text().contains("v6") && static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().contains("v6"))
            {
                static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(false);
                LOG_INFO("%s is not functional anymore", static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().toStdString().c_str());
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
    if (packetproto->fields) {
        ui->verticalLayout_fields->insertWidget(index - 1, &packetproto->fields->grpbox);
        LOG_INFO("Add headers for %s", packetproto->fields->grpbox.title().toStdString().c_str());
    }

    ui->verticalLayout_packet->setAlignment(Qt::AlignCenter);

    packetproto->show();

    // Init custom fileds layout

}

// Remove widget from Packet layout when clicked
void MainWindow::clickedPacketProto()
{
    QString tmp = ((CProtocol *)sender())->text();
    int tmp2 = ((CProtocol *)sender())->layer;
    LOG_INFO("Delete %s of layer %d", tmp.toStdString().c_str(), ((CProtocol *)sender())->layer);
    QGridLayout *grp = layer_groups[((CProtocol *)sender())->layer - 1];
    if (((CProtocol *)sender())->text().contains("ICMP"))
        grp = layer_groups[((CProtocol *)sender())->layer];
    for (int i = 0; i < grp->count(); ++i)
    {
        static_cast<CProtocol *>(grp->itemAt(i)->widget())->setEnabled(true);
        LOG_INFO("%s is back to enabled", static_cast<CProtocol *>(grp->itemAt(i)->widget())->text().toStdString().c_str());
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
    LOG_DEBUG("Delete sender");
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
    LOG_INFO("Press send");

    int ret = PacketValidator::validateIfc(packetHandler, ui->lineEdit_Ifc);
    if (ret == -1)
    {
        LOG_ERROR("Interface validation failed: %s", ui->lineEdit_Ifc->text().toStdString().c_str());
        return;
    }
    PacketValidator::validateParams(packetHandler, ui->verticalLayout_packet);

    packetHandler.Ifc = ui->lineEdit_Ifc->text();
    packetHandler.period = ui->spinBox_period->value();
    packetHandler.packetCount = ui->spinBox_count->value();

    ret = packetHandler.sendPacket();
    if (ret == -1)
    {
        LOG_ERROR("Send packet failed");
        return;
    }
}

// TODOs

// 1. add "Autofill strings to lineedits as a hint"
// 2. add default values to particular fields
// 3. add validations for packets
// 4. Varify packet
// 6. Auto open wireshark to look for traffic ?

// 5. Open and parse file


// Save packets
void MainWindow::on_pushButton_3_clicked()
{
    PacketValidator::validateParams(packetHandler, ui->verticalLayout_packet);
    PacketSaver::savePacket(packetHandler);
}

// Packet scenarios
void MainWindow::on_pushButton_clicked()
{
    LOG_DEBUG(__FUNCTION__);
    ScenariosWindow *sw = new ScenariosWindow();
    sw->m = this;
    sw->show();
    sw->changeLanguage();
    this->hide();
}

// log button
void MainWindow::on_pushButton_18_clicked()
{
    LOG_DEBUG(__FUNCTION__);
    FileDisplayer fileDisplayer;

    fileDisplayer.exec();

}

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

void MainWindow::on_pushButton_4_clicked()
{


    // Open a file using a dialog window
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", "", "All Files (*)");
    if (filePath.isEmpty())
    {
        qDebug() << "No file selected.";
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open the file.";
        return;
    }

    QTextStream in(&file);
    QStringList lines;

    // Read the file line by line
    while (!in.atEnd())
    {
        QString line = in.readLine();
        lines.append(line);
    }

    file.close();

    // Check if the file format matches the expected format
    if (lines.size() < 4 || !lines[0].startsWith("#!/usr/bin/python3") || !lines[1].startsWith("from scapy.all import *"))
    {
        qDebug() << "Invalid file format.";
        return;
    }

    // Remove the first two lines
    lines.removeFirst();
    lines.removeFirst();

    // Define a regular expression pattern to match variable assignments
    QRegularExpression pattern("(\\w+)\\s*=\\s*(.*)");

    QHash<QString, QString> variables;

    // Process each line
    for (const QString& line : lines)
    {
        // Check if the line matches the variable assignment pattern
        QRegularExpressionMatch match = pattern.match(line);
        if (match.hasMatch())
        {
            // Extract the variable name and parameter
            QString variableName = match.captured(1);
            QString parameter = match.captured(2).trimmed();

            // Save the variable and its parameter in the hash
            variables[variableName] = parameter;
        }

    }

    // Print the parsed variables and parameters
    QHashIterator<QString, QString> iterator(variables);
    while (iterator.hasNext())
    {
        iterator.next();
        qDebug() << iterator.key() << ": " << iterator.value();
        if (iterator.key() == "Ethernet")
        {
            addProtoAction(ui->pushButton_14, new CEtherFields(ui->verticalLayout_fields));
        }
        else if (iterator.key() == "IPv4")
        {
            addProtoAction(ui->pushButton_10, new CIpv4fields(ui->verticalLayout_fields));
        } else if (iterator.key() == "ICMP")
        {
            addProtoAction(ui->pushButton_12, new Cicmp(ui->verticalLayout_fields));
        }
    }

}

