#include "Worker.hpp"

#include <QDebug>
#include <QThread>
#include <QRandomGenerator>

#define CURRENT_THREAD_FOR_LOG "on thread" << QThread::currentThread()
#define LOG_FUNC_INFO qInfo() << Q_FUNC_INFO << "called" << CURRENT_THREAD_FOR_LOG;

namespace lesson_3_12 {

Worker::Worker(QSemaphore *sema, QList<qint32> *values, QObject *parent)
    : QObject(parent)
    , m_sema(sema)
    , m_values(values)
{
    LOG_FUNC_INFO;
}

Worker::~Worker(void) {
    LOG_FUNC_INFO;
}

void Worker::run(void) {
    LOG_FUNC_INFO;

    qint32 max = QRandomGenerator::global()->bounded(1, m_values->size());

    qInfo() << Q_FUNC_INFO << "Acquiring" << m_sema->available() << CURRENT_THREAD_FOR_LOG;
    m_sema->acquire(max);

    qInfo() << Q_FUNC_INFO << "Acquired" << m_sema->available() << CURRENT_THREAD_FOR_LOG;
    qint32 val(0);
    for (qint32 i(0); i < max; ++i) {
        qInfo() << Q_FUNC_INFO << "Mofify" << i << CURRENT_THREAD_FOR_LOG;
        //val = QRandomGenerator::global()->bounded(100);
        //m_values->replace(i, val);
        QThread::currentThread()->msleep(250);
    }

    qInfo() << Q_FUNC_INFO << "Release" << max << CURRENT_THREAD_FOR_LOG;
    m_sema->release(max);
}

}   // !lesson_3_12;