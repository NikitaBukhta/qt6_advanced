#include "Test.hpp"

#include <QDebug>
#include <QThread>

namespace lesson_3_6{

Test::Test(QObject *parent)
    : QObject(parent){

}

void Test::run(void){
    qInfo() << "Running" << QThread::currentThread();
    m_timer.singleShot(3000, this, &Test::timeout);
    qInfo() << "Running" << QThread::currentThread();
}

void Test::timeout(void){
    qInfo() << "Timeout" << QThread::currentThread();
}

};