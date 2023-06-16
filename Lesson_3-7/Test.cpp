#include "Test.hpp"

#include <QDebug>

namespace lesson_3_7{

Test::Test(QObject *parent) 
    : QThread(parent){

}

void Test::run(void){
    // Notice: after 3 seconds nothing happens!
    m_timer.singleShot(3000, this, &Test::test);
    test();
}

void Test::test(void){
    // Notice: this gets run last!
    qInfo() << "TESTING" << currentThread();

    terminate();

    // Bad things happen from here;
}

}   // !lesson_3_7;