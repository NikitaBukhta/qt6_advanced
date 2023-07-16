#include "Worker.hpp"

#include <QCoreApplication>
#include <QThread>
#include <QObject>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    QThread::currentThread()->setObjectName("Main thread");
    QThread worker_thread;
    worker_thread.setObjectName("Worker thread");

    lesson_4_27::Worker *worker = new lesson_4_27::Worker();
    worker->moveToThread(&worker_thread);
    QObject::connect(&worker_thread, &QThread::started, worker, lesson_4_27::Worker::start);
    worker_thread.start();

    return app.exec();
}