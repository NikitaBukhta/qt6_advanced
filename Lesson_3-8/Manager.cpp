#include "Manager.hpp"
#include "Counter.hpp"

#include <QDebug>

namespace lesson_3_8 {

Manager::Manager(QObject *parent) : QObject(parent) {
    for (quint8 i(0); i < 5; ++i) {
        QThread *thread = new QThread(this);
        thread->setObjectName("Thread " + QString::number(i));
        qInfo() << "Created: " << thread->objectName();
        connect(thread, &QThread::started, this, &Manager::started);
        connect(thread, &QThread::finished, this, &Manager::finished);
        m_threads.append(thread);
    }
}

void Manager::start(void) {
    qInfo() << "Starting...";

    for (const auto &thread : m_threads) {
        qInfo() << "Starting: " << thread->objectName();
        Counter *c = new Counter();
        c->moveToThread(thread);
        connect(thread, &QThread::started, c, &Counter::start);
        thread->start();
    }
}

void Manager::started(void) {
    qInfo() << "Starting" << sender();
    QThread *thread = qobject_cast<QThread*>(sender());
    if (thread) {
        qInfo() << "Started: " << thread->objectName();
    }
}

void Manager::finished(void) {
    qInfo() << "Finishing" << sender();
    QThread *thread = qobject_cast<QThread*>(sender());
    if(thread) {
        qInfo() << "Childer" << thread->children().length();
        qInfo() << "Finished: " << thread->objectName();
    }

    m_threads.removeAll(thread);
    delete thread;
}

}   // !lesson_3_8;