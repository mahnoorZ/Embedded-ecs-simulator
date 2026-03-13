#include <QApplication>
#include <thread>

#include "controller.hpp"
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Controller controller;

    std::thread controller_thread([&controller]() {
        controller.run();
    });

    MainWindow window(&controller);
    window.show();

    int result = app.exec();

    controller_thread.join();

    return result;
}