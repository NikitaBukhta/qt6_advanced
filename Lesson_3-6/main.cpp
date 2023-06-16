/* Lesson description:
 *
 * What?
 * Threaded example;
 * 
 * Why?
 * To understand what is happening when we run code;
 * 
 * How?
 * Threaded code;
 */

#include <QCoreApplication>
/* Lesson description:
 * 
 * What
 * Threaded example;
 * 
 * Why
 * Understand whats happening when we run code;
 * 
 * How
 * Threaded code;
 */

#include <QThread>
#include <QDebug>

#include "Test.hpp"

int main(int argc, char **argv){
    using namespace lesson_3_6;

    QCoreApplication app(argc, argv);
    
    QThread::currentThread()->setObjectName("Main Thread");

    qInfo() << "Program has been started" << QThread::currentThread();

    QThread worker;
    worker.setObjectName("Worker thread");

    Test test;
    test.moveToThread(&worker);
    QObject::connect(&worker, &QThread::started, &test, &Test::run, Qt::ConnectionType::QueuedConnection);
    worker.start();

    qInfo() << "Program finished" << QThread::currentThread();

    return app.exec();
}