#include "Counter.hpp"

#include <QDebug>
#include <QThread>
#include <QRandomGenerator>

#define LOG_FUNC_INFO qInfo() << Q_FUNC_INFO << "called on thread:" << QThread::currentThread();

namespace lesson_3_9 {

void Counter::run(void) {
    LOG_FUNC_INFO;

    for (qint32 i(0); i < 20; ++i) {
        qInfo() << Q_FUNC_INFO << QThread::currentThread() << "=" << i;
        quint32 value = static_cast<quint32>(QRandomGenerator::global()->bounded(100));
        QThread::currentThread()->msleep(value);
    }
}

}   // !lesson_3_9;