/* Lesson description:
 *
 * What
 * Inheriting QThread;
 * 
 * Why
 * This is BAD, do not do this!
 * Folks familiar with java will try this
 * Its bad because you can easily break the way threading works
 * This is super confusing as QT documentation;
 * 
 * How
 * Threaded code;
 */

#include "Worker.hpp"
#include "Test.hpp"

#include <QCoreApplication>
#include <QThread>

int main(int argc, char **argv){
    using namespace lesson_3_7;

    QCoreApplication app(argc, argv);
    QThread::currentThread()->setObjectName("Main Thread");

    Test thread;
    thread.setObjectName("Thread 1");

    Worker worker;
    worker.moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, &worker, &Worker::work);
    thread.start();

    return app.exec();
}