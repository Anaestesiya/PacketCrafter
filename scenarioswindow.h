#ifndef SCENARIOSWINDOW_H
#define SCENARIOSWINDOW_H

#include <QMainWindow>

#include "mainwindow.h"

namespace Ui {
class ScenariosWindow;
}

class ScenariosWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScenariosWindow(QWidget *parent = nullptr);
    ~ScenariosWindow();

    MainWindow *m;

private slots:
    void on_pushButton_clicked();

private:
    Ui::ScenariosWindow *ui;
};

#endif // SCENARIOSWINDOW_H
