#include "Counter.hpp"

#include <QThread>
#include <QDebug>

namespace lesson_3_10{

Counter::Counter(QMutex *mutex, qint32 *value)
    : m_mutex(mutex)
    , m_value(value)
{    
    qInfo() << Q_FUNC_INFO << "called";
}

Counter::~Counter(){
    qInfo() << Q_FUNC_INFO << "called";
}

void Counter::run(void){
    // Wait until we can do staff...;

    m_mutex->lock();    // We will wait until we can lock!;

    QThread::currentThread()->msleep(50);
    *m_value += 1;
    qInfo() << Q_FUNC_INFO << *m_value << QThread::currentThread();

    m_mutex->unlock();  // Other threads can lock;
}

}