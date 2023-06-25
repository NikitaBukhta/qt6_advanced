/* Lesson description:
 *
 * What:
 * TCP sockets;
 * 
 * Why:
 * We need to understand the conection life cycle;
 * 
 * How:
 * QTcpSocket;
 */

#include "Client.hpp"

#include <QCoreApplication>

using namespace lesson_4_19;

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    Client client;
    // if not right address or port, the errors should be occured; 
    client.connect_to_host("www.voidrealms.com", 80);

    return app.exec();
}