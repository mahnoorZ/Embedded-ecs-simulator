#ifndef SENSOR_MANAGER_HPP
#define SENSOR_MANAGER_HPP

#include "types.hpp"

class SensorManager {

public:

    SensorManager();

    void update();

    const SensorData& getSensors() const;
    void injectLowBattery(bool enable);
    void injectOverTemp(bool enable);
    void injectCommsFailure(bool enable);
    void clearFaults();

private:

    SensorData sensors;
    bool fault_low_battery = false;
    bool fault_overtemp = false;
    bool fault_comms = false;

};

#endif