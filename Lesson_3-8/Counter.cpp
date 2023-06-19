#include "Counter.hpp"

#include <QDebug>
#include <QThread>
#include <QRandomGenerator>

namespace lesson_3_8 {

Counter::Counter(QObject *parent) : QObject(parent) {
    qInfo() << this << "Constructed";
}

Counter::~Counter(void) {
    qInfo() << this << "Deconstructed";
}

void Counter::start(void) {
    for (quint8 i(0); i < 20; ++i) {
        qInfo() << QThread::currentThread()->objectName() << " = " << i;
        auto sleep_time = static_cast<quint32>(QRandomGenerator::global()->bounded(500));
        QThread::currentThread()->msleep(sleep_time);
        qInfo() << QThread::currentThread()->objectName() << " Completed";
    }

    qInfo() << this << "Completed";
    deleteLater();

    QThread::currentThread()->quit();
}

}   // !lesson_3_8;