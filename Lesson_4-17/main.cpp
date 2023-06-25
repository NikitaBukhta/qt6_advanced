/* Lesson description:
 *
 * What:
 * UDP;
 * 
 * Why:
 * We want to send and receive and not care about a connection;
 * 
 * How
 * QUdpSocket;
 */

#include "Worker.hpp"

#include <QCoreApplication>

using namespace lesson_4_17;

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    Worker worker;
    worker.start();

    return app.exec();
}