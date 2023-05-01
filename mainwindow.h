#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocale>
#include <QTranslator>
#include <QGridLayout>

#include "CProtocol.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addProtoAction(CProtocol *proto);

private slots:
    void on_pushButton_set_UA_clicked();

    void on_pushButton_set_EN_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_5_clicked();

    void clickedPacketProto();

    void on_pushButton_14_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    QTranslator translator;
    QGridLayout *layer_groups[5];
};
#endif // MAINWINDOW_H
