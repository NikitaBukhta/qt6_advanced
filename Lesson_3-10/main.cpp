#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QThreadPool>
#include <QMutex>
#include <QTypeInfo>

#include "Counter.hpp"

using namespace lesson_1;

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QThread::currentThread()->setObjectName("Main Thread");
    QThreadPool *pool = QThreadPool::globalInstance();

    QSharedPointer<QMutex> mutex;
    QSharedPointer<qint32> value = 0;
    qInfo() << pool->maxThreadCount() << " threads";

    for (qint32 i = 0, limit = 100; i < limit; ++i){
        Counter *counter = new Counter(mutex, value);
        counter->setAutoDelete(true);
        pool->start(counter);
    }

    return app.exec();
}
