#include "sensor_manager.hpp"
#include <cstdlib>

SensorManager::SensorManager() {}

void SensorManager::update() {

    sensors.engine_rpm = 1500 + rand() % 300;

    sensors.battery_voltage = 12.2;

    sensors.oil_temperature = 65;

    sensors.communication_ok = true;

    if (fault_low_battery) {
        sensors.battery_voltage = 9.5;
    }

    if (fault_overtemp) {
        sensors.oil_temperature = 110;
    }

    if (fault_comms) {
        sensors.communication_ok = false;
    }
}
// void SensorManager::update() {
    // // simulate ignition turning on
    // sensors.ignition_on = true;

    // // simulate operator pressing start
    // sensors.start_command = true;

    // // emergency stop not pressed
    // sensors.emergency_stop = false;

    // simulate sensors

    // sensors.engine_rpm = rand() % 2500;

    // sensors.battery_voltage = 11.5 + static_cast<float>(rand()) / RAND_MAX;

    // sensors.hydraulic_pressure = 100 + rand() % 50;

    // sensors.oil_temperature = 50 + rand() % 20;

    // sensors.vehicle_speed = rand() % 20;

    // sensors.communication_ok = true;

//     // intentionally force abnormal values for testing
//     sensors.engine_rpm = 1800.0;
//     sensors.battery_voltage = 10.2;      // critical low battery
//     sensors.hydraulic_pressure = 110.0;
//     sensors.oil_temperature = 98.0;      // critical overtemperature
//     sensors.vehicle_speed = 12.0;
//     sensors.communication_ok = true;
// }


const SensorData& SensorManager::getSensors() const {

    return sensors;

}

void SensorManager::injectLowBattery(bool enable) {
    fault_low_battery = enable;
}

void SensorManager::injectOverTemp(bool enable) {
    fault_overtemp = enable;
}

void SensorManager::injectCommsFailure(bool enable) {
    fault_comms = enable;
}

void SensorManager::clearFaults() {
    fault_low_battery = false;
    fault_overtemp = false;
    fault_comms = false;
}