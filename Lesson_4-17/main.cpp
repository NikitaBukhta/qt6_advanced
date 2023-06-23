#include "Worker.hpp"

#include <QCoreApplication>

using namespace lesson_4_17;

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    Worker worker;
    worker.start();

    return app.exec();
}