#include "Consumer.hpp"

#include <QDebug>
#include <QThread>

#define CURRENT_THREAD_FOR_LOG "on thread" << QThread::currentThread()
#define LOG_FUNC_INFO qInfo() << Q_FUNC_INFO << "called" << CURRENT_THREAD_FOR_LOG;

namespace lesson_3_13 {

Consumer::Consumer(QMutex &mutex, QWaitCondition &value_ready, qint32 &value, QObject *parent)
    : m_mutex(mutex)
    , m_value_ready(value_ready)
    , m_value(value)
{
    LOG_FUNC_INFO;
}

Consumer::~Consumer(void) {
    LOG_FUNC_INFO;
}

void Consumer::run(void) {
    LOG_FUNC_INFO;
    m_mutex.lock();
    qInfo() << Q_FUNC_INFO << "mutex locked" << CURRENT_THREAD_FOR_LOG;
    if (!m_value) {
        qInfo() << Q_FUNC_INFO << "Waiting for update the m_value" << CURRENT_THREAD_FOR_LOG;
        m_value_ready.wait(&m_mutex);
    }

    qInfo() << Q_FUNC_INFO << "Consuming" << m_value << CURRENT_THREAD_FOR_LOG;
}

}   // !lesson_3_13;