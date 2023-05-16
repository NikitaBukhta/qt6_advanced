/* Lesson description:
 *
 * What?
 * Asynchronous example;
 * 
 * Why?
 * To understand what is happening when we run code;
 * 
 * How?
 * Asynchronous code;
 */

#include <QCoreApplication>
#include <QThread>
#include <QTimer>

void test_current_thread(void){
    qInfo() << "Testing" << QThread::currentThread();
}

int main(int argc, char **argv){
    QCoreApplication app(argc, argv);

    QThread::currentThread()->setObjectName("Main Thread");
    qInfo() << "Program has been started" << QThread::currentThread();

    QTimer timer;
    timer.singleShot(3000, &test_current_thread);

    qInfo() << "Program finished" << QThread::currentThread();

    return app.exec();
}