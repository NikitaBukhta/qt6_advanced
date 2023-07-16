/* Lesson description:
 *
 * What:
 * Asynchronous TCP;
 * 
 * Why:
 * This is how you would typically work with it;
 * 
 * How:
 * Signals and slots;
 * Note this blocks in the slots!;
 */

#include "Client.hpp"

#include <QCoreApplication>
#include <QThread>
#include <QDebug>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    QThread::currentThread()->setObjectName("Main Thread");

    lesson_4_24::Client client;
    client.connect_to_host("www.voidrealms.com", 80);

    qInfo() << Q_FUNC_INFO << "Free to do other things";

    return app.exec();
}