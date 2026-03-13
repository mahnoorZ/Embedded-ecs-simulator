#include "controller.hpp"
#include "logger.hpp"
#include <thread>
#include <chrono>

Controller::Controller() {}

void Controller::run() {

    Logger::log("Controller starting...");

    while (true) {

        sensor_manager.update();

        const SensorData& sensors = sensor_manager.getSensors();

        diagnostics_manager.evaluate(sensors);

        state_machine.update(
            sensors,
            diagnostics_manager.hasCriticalFault(),
            diagnostics_manager.hasWarning()
        );

        if (diagnostics_manager.hasCriticalFault()) {
            Logger::log("SYSTEM ENTERING FAULT STATE");
        }

        can_interface.transmitState(state_machine.getState());

        can_interface.transmitSensors(sensors);

        can_interface.transmitFaults(diagnostics_manager.getActiveFaults());

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
    }

}

const SensorData& Controller::getSensors() const {
    return sensor_manager.getSensors();
}

ECSState Controller::getState() const {
    return state_machine.getState();
}

void Controller::toggleIgnition() {

    SensorData& sensors = const_cast<SensorData&>(sensor_manager.getSensors());
    sensors.ignition_on = !sensors.ignition_on;

}

void Controller::startEngine() {

    SensorData& sensors = const_cast<SensorData&>(sensor_manager.getSensors());
    sensors.start_command = true;

}

void Controller::emergencyStop() {

    SensorData& sensors = const_cast<SensorData&>(sensor_manager.getSensors());
    sensors.emergency_stop = true;

}

void Controller::injectLowBattery() {
    sensor_manager.injectLowBattery(true);
}

void Controller::injectOverTemp() {
    sensor_manager.injectOverTemp(true);
}

void Controller::injectCommsFailure() {
    sensor_manager.injectCommsFailure(true);
}

void Controller::clearFaults() {
    sensor_manager.clearFaults();
}