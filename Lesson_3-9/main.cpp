#include "Counter.hpp"

#include <QCoreApplication>
#include <QThreadPool>
#include <QDebug>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    QThread::currentThread()->setObjectName("Main Thread");

    QThreadPool *pool = QThreadPool::globalInstance();
    qInfo() << Q_FUNC_INFO << "Max threads count:" << pool->maxThreadCount();

    for (qint32 i(0); i < 100; ++i) {
        lesson_3_9::Counter *counter = new lesson_3_9::Counter();
        counter->setAutoDelete(true);
        pool->start(counter);
    }

    return app.exec();
}