/* Lesson description:
 *
 * What:
 * Mutex locker;
 * 
 * Why:
 * We want to protect an object from thread issues;
 * But we want to make it easier;
 * 
 * How:
 * QMutexLocker;
 */

#include "Counter.hpp"

#include <QCoreApplication>
#include <QThread>
#include <QThreadPool>
#include <QMutex>
#include <QDebug>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    QThread::currentThread()->setObjectName("Main Thread");
    QThreadPool *pool = QThreadPool::globalInstance();

    QMutex mutex;
    qint32 value(0);

    qInfo() << Q_FUNC_INFO << "max threads count:" << pool->maxThreadCount();

    for (qint32 i(0); i < 100; ++i) {
        lesson_3_11::Counter *counter = new lesson_3_11::Counter(&mutex, &value);
        counter->setAutoDelete(true);
        pool->start(counter);
    }

    return app.exec();
}