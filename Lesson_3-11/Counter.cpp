#include "Counter.hpp"

#include <QDebug>
#include <QMutexLocker>
#include <QThread>

namespace lesson_3_11 {

Counter::Counter(QMutex *mutex, qint32 *counter)
    : m_mutex(mutex)
    , m_counter(counter)
{
    qInfo() << Q_FUNC_INFO << "called";
}

Counter::~Counter(void)
{
    qInfo() << Q_FUNC_INFO << "called";
}

void Counter::run(void) {
    QMutexLocker lock(m_mutex);
    *m_counter += 1;

    qInfo() << Q_FUNC_INFO << "counter:" << *m_counter 
        << "thread:" << QThread::currentThread();
}

}   // !lesson_3_11;