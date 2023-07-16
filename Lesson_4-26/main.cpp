/* Lesson description:
 *
 * What:
 * Threaded TCP;
 * 
 * Why:
 * We want to use both threaded and sync code;
 * 
 * How:
 * QThread and QTcpSocket;
 */

#include "Client.hpp"

#include <QCoreApplication>
#include <QThread>
#include <QObject>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    QThread::currentThread()->setObjectName("Main Thread");

    QThread client_thread;
    client_thread.setObjectName("Client thread");

    lesson_4_26::Client *client = new lesson_4_26::Client();
    client->set_host("voidrealms.com");
    client->set_port(80);

    client->moveToThread(&client_thread);

    QObject::connect(&client_thread, &QThread::started, 
        client, &lesson_4_26::Client::run
    );

    client_thread.start();

    return app.exec();
}