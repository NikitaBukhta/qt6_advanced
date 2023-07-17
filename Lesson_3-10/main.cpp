/* Lesson description:
 *
 * What:
 * Mutex;
 * 
 * Why:
 * We want to protect an object from thread issues;
 * 
 * How:
 * QMutex;
 * 
 * Two threads updating the same thing at the same time;
 */

#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QThreadPool>
#include <QMutex>
#include <QTypeInfo>

#include "Counter.hpp"

using namespace lesson_3_10;

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QThread::currentThread()->setObjectName("Main Thread");
    QThreadPool *pool = QThreadPool::globalInstance();

    QMutex mutex;
    qint32 value = 0;
    qInfo() << pool->maxThreadCount() << " threads";

    for (qint32 i = 0, limit = 100; i < limit; ++i){
        Counter *counter = new Counter(&mutex, &value);
        counter->setAutoDelete(true);
        pool->start(counter);
    }

    return app.exec();
}
