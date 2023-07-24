/* Lesson description:
 *
 * What:
 * Wait condition;
 * 
 * Why:
 * Sync threads;
 * 
 * How:
 * QWaitCondition;
 */

#include "Producer.hpp"
#include "Consumer.hpp"

#include <QCoreApplication>
#include <QWaitCondition>
#include <QMutex>
#include <QThread>
#include <QObject>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    QWaitCondition value_ready;
    QMutex mutex;
    QThread producer_thread;
    QThread consumer_thread;
    qint32 value(0);

    producer_thread.setObjectName("Producer thread");
    consumer_thread.setObjectName("Consumer thread");

    lesson_3_13::Producer *producer = new lesson_3_13::Producer(mutex, value_ready, value);
    lesson_3_13::Consumer *consumer = new lesson_3_13::Consumer(mutex, value_ready, value);

    producer->moveToThread(&producer_thread);
    consumer->moveToThread(&consumer_thread);

    QObject::connect(&producer_thread, &QThread::started, producer, &lesson_3_13::Producer::run);
    QObject::connect(&consumer_thread, &QThread::started, consumer, &lesson_3_13::Consumer::run);

    producer_thread.start();
    consumer_thread.start();

    return app.exec();
}