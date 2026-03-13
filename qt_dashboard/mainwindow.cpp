#include "mainwindow.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

QString stateToString(ECSState state) {

    switch (state) {

        case ECSState::Off:
            return "OFF";

        case ECSState::Boot:
            return "BOOT";

        case ECSState::Idle:
            return "IDLE";

        case ECSState::Running:
            return "RUNNING";

        case ECSState::Warning:
            return "WARNING";

        case ECSState::Fault:
            return "FAULT";

        case ECSState::EmergencyStop:
            return "EMERGENCY STOP";

        default:
            return "UNKNOWN";
    }

}

MainWindow::MainWindow(Controller* controller, QWidget *parent)
    : QMainWindow(parent), controller(controller)
{

    QWidget* central = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();

    state_label = new QLabel("State: OFF");
    rpm_label = new QLabel("RPM: 0");
    battery_label = new QLabel("Battery: 12.0");
    temp_label = new QLabel("Temp: 0");

    ignition_button = new QPushButton("Toggle Ignition");
    start_button = new QPushButton("Start Engine");
    estop_button = new QPushButton("Emergency Stop");

    low_battery_button = new QPushButton("Inject Low Battery");
    overtemp_button = new QPushButton("Inject Overtemp");
    comms_button = new QPushButton("Inject Comms Failure");
    clear_faults_button = new QPushButton("Clear Faults");

    layout->addWidget(state_label);
    layout->addWidget(rpm_label);
    layout->addWidget(battery_label);
    layout->addWidget(temp_label);

    layout->addWidget(ignition_button);
    layout->addWidget(start_button);
    layout->addWidget(estop_button);

    layout->addWidget(low_battery_button);
    layout->addWidget(overtemp_button);
    layout->addWidget(comms_button);
    layout->addWidget(clear_faults_button);

    central->setLayout(layout);
    setCentralWidget(central);

    update_timer = new QTimer(this);

    connect(ignition_button, &QPushButton::clicked, [this]() {

        this->controller->toggleIgnition();

    });

    connect(start_button, &QPushButton::clicked, [this]() {

        this->controller->startEngine();

    });

    connect(estop_button, &QPushButton::clicked, [this]() {

        this->controller->emergencyStop();

    });

    connect(low_battery_button, &QPushButton::clicked, [this]() {
        this->controller->injectLowBattery();
    });

    connect(overtemp_button, &QPushButton::clicked, [this]() {
        this->controller->injectOverTemp();
    });

    connect(comms_button, &QPushButton::clicked, [this]() {
        this->controller->injectCommsFailure();
    });

    connect(clear_faults_button, &QPushButton::clicked, [this]() {
        this->controller->clearFaults();
    });

    connect(update_timer, &QTimer::timeout, [this]() {

        const SensorData& sensors = this->controller->getSensors();

        state_label->setText(
            "State: " + stateToString(this->controller->getState())
        );

        rpm_label->setText(
            "RPM: " + QString::number((int)sensors.engine_rpm)
        );

        battery_label->setText(
            "Battery: " + QString::number(sensors.battery_voltage)
        );

        temp_label->setText(
            "Temp: " + QString::number(sensors.oil_temperature)
        );

    });

    update_timer->start(500);

}