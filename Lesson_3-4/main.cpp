/* Lesson description:
 *
 * What?
 * Synchronoues example;
 * 
 * Why?
 * To understand what is happening when we run code;
 * 
 * How?
 * Synchronous code;
 */

#include <QCoreApplication>
#include <QThread>

void test_current_thread(void){
    qInfo() << "Testing" << QThread::currentThread();
}

int main(int argc, char **argv){
    QCoreApplication app(argc, argv);

    QThread::currentThread()->setObjectName("Main Thread");
    qInfo() << "Program has been started" << QThread::currentThread();
    test_current_thread();
    qInfo() << "Program finished" << QThread::currentThread();

    return app.exec();
}