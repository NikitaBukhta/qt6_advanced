/* Lesson Description:
 *
 * What:
 * Thread lifecycle;
 * 
 * Why:
 * Threads might not live forever;
 * 
 * How:
 * Threaded code;
 */

#include "Manager.hpp"

#include "QCoreApplication"
#include <QDebug>
#include <QThread>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    QThread::currentThread()->setObjectName("Main");

    lesson_3_8::Manager manager;
    manager.start();

    return app.exec();
}