#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "sensor_manager.hpp"
#include "state_machine.hpp"
#include "diagnostics_manager.hpp"
#include "can_interface.hpp"

class Controller {

public:

    Controller();

    void run();

    const SensorData& getSensors() const;
    ECSState getState() const;
    void toggleIgnition();
    void startEngine();
    void emergencyStop();
    void injectLowBattery();
    void injectOverTemp();
    void injectCommsFailure();
    void clearFaults();

private:

    SensorManager sensor_manager;
    DiagnosticsManager diagnostics_manager;
    StateMachine state_machine;
    CanInterface can_interface;

};



#endif