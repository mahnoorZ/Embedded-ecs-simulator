cmake_minimum_required(VERSION 3.16)

project(vehicle_ecs_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/Users/mahnooraftab/anaconda3")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

include_directories(
    include
    qt_dashboard
)

add_executable(vehicle_ecs_simulator

    src/main.cpp
    src/controller.cpp
    src/logger.cpp
    src/sensor_manager.cpp
    src/state_machine.cpp
    src/diagnostics_manager.cpp
    src/can_interface.cpp

    qt_dashboard/mainwindow.cpp
)

target_link_libraries(vehicle_ecs_simulator Qt5::Widgets)