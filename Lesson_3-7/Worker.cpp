#include "Worker.hpp"

#include <QThread>
#include <QDebug>

namespace lesson_3_7{

Worker::Worker(QObject *parent) : QObject(parent){

}

void Worker::work(){
    const uint8_t LOOP_COUNT = 10;
    for(uint8_t i = 0; i < LOOP_COUNT; ++i){
        qInfo() << "Work" << static_cast<int32_t>(i) << QThread::currentThread();
        QThread::currentThread()->msleep(1000);
    }
}

}   // !lesson_3_7;