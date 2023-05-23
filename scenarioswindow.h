#ifndef SCENARIOSWINDOW_H
#define SCENARIOSWINDOW_H

#include <QMainWindow>

#include "mainwindow.h"
#include "scenarios/scenario.h"

namespace Ui {
class ScenariosWindow;
}

class ScenariosWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScenariosWindow(QWidget *parent = nullptr);
    ~ScenariosWindow();


    void showScenario(Scenario *scenario);
    void hideScenario(Scenario *scenario);

    void changeLanguage();

    MainWindow *m;
    Scenario *activeScenario;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_UA_clicked();

    void on_pushButton_EN_clicked();

private:
    Ui::ScenariosWindow *ui;
};

#endif // SCENARIOSWINDOW_H
