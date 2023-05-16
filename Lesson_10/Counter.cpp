#include "Counter.hpp"

#include <QThread>
#include <QDebug>

namespace lesson_1{

Counter::Counter(QWeakPointer<QMutex> mutex, QWeakPointer<qint32> value)
    : m_mutex(mutex.toStrongRef())
    , m_value(value.toStrongRef()){
    
    qDebug() << "[Counter][Counter] constructor called";
}

Counter::~Counter(){
    qDebug() << "[Counter][Counter] destructor called";
}

void Counter::run(void){
    // Wait until we can do staff...;

    m_mutex->lock();    // We will wait until we can lock!;

    QThread::currentThread()->msleep(50);
    *m_value += 1;
    qInfo() << *m_value << QThread::currentThread();

    m_mutex->unlock();  // Other threads can lock;
}

}