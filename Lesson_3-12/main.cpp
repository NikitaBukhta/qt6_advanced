/* Lesson Description:
 *
 * What:
 * Semaphores;
 * 
 * Why:
 * Generalize a mutex;
 * Lock and unlock multople resources;
 * 
 * How:
 * QSemaphore;
 */

#include "Worker.hpp"

#include <QCoreApplication>
#include <QList>
#include <QSemaphore>
#include <QThread>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    QList<qint32> values;
    values.resize(10);
    values.fill(0);

    QSemaphore sema(values.size());
    qInfo() << Q_FUNC_INFO << values;

    QThread thread_1;
    QThread thread_2;

    thread_1.setObjectName("Thread 1");
    thread_2.setObjectName("Thread 2");

    lesson_3_12::Worker worker_1(&sema, &values);
    lesson_3_12::Worker worker_2(&sema, &values);
    worker_1.moveToThread(&thread_1);
    worker_2.moveToThread(&thread_2);

    QObject::connect(&thread_1, &QThread::started, &worker_1, &lesson_3_12::Worker::run);
    QObject::connect(&thread_2, &QThread::started, &worker_2, &lesson_3_12::Worker::run);

    thread_1.start();
    thread_2.start();

    return app.exec();
}