#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "controller.hpp"
#include <QTimer>

class QLabel;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Controller* controller, QWidget *parent = nullptr);

private:

    Controller* controller;

    QLabel* state_label;
    QLabel* rpm_label;
    QLabel* battery_label;
    QLabel* temp_label;

    QPushButton* ignition_button;
    QPushButton* start_button;
    QPushButton* estop_button;

    QTimer* update_timer;

    QPushButton* low_battery_button;
    QPushButton* overtemp_button;
    QPushButton* comms_button;
    QPushButton* clear_faults_button;

};

#endif