#include "Producer.hpp"

#include <QDebug>
#include <QThread>
#include <QRandomGenerator>

#define CURRENT_THREAD_FOR_LOG "on thread" << QThread::currentThread()
#define LOG_FUNC_INFO qInfo() << Q_FUNC_INFO << "called" << CURRENT_THREAD_FOR_LOG;

namespace lesson_3_13 {

Producer::Producer(QMutex &mutex, QWaitCondition &value_ready, qint32 &value, QObject *parent)
    : m_mutex(mutex)
    , m_value_ready(value_ready)
    , m_value(value)
{
    LOG_FUNC_INFO;
}

Producer::~Producer(void) {
    LOG_FUNC_INFO;
}

void Producer::run(void) {
    LOG_FUNC_INFO;
    QThread::currentThread()->msleep(3000);

    m_mutex.lock();
    m_value = QRandomGenerator::global()->bounded(1000);
    qInfo() << "Producer warking up consumer" << CURRENT_THREAD_FOR_LOG;
    m_mutex.unlock();

    m_value_ready.wakeAll();
}

}   // !lesson_3_13;