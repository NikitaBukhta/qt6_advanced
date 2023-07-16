/* Lesson description:
 *
 * What:
 * Asynchronous UDP;
 * 
 * Why:
 * This is how you normally work with it;
 * 
 * How:
 * Remember slots blocks!;
 */

#include "Worker.hpp"

#include <QCoreApplication>
#include <QThread>
#include <QDebug>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    QThread::currentThread()->setObjectName("Main Thread");

    lesson_4_25::Worker worker;
    worker.start();

    qInfo() << Q_FUNC_INFO << "Free to do other things";

    return app.exec();
}