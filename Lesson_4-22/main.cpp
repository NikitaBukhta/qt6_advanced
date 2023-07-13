/* Lesson description:
 *
 * What:
 * Synchronous TCP
 * 
 * Why:
 * We want to use TCP, and block while doing it;
 * 
 * How:
 * Example code;
 */

#include <QCoreApplication>
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QByteArray>

const QString SERVER_DOMAIN = "voidrealm.com";
const quint16 SERVER_PORT = 80;

void send_data(QTcpSocket &socket, const QByteArray &data) {
    socket.write(data);
    socket.waitForBytesWritten();
}

QByteArray read_data(QTcpSocket &socket) {
    if (socket.waitForReadyRead(60000)) {
        return std::move(socket.readAll());
    }

    return {};
}

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    QTcpSocket socket;
    socket.connectToHost(SERVER_DOMAIN, SERVER_PORT);
    qInfo() << "Connection to the host" << SERVER_DOMAIN << ":" << SERVER_PORT;

    if (socket.waitForConnected(6000)) {
        QByteArray request;
        request.append("GET / HTTP/1.1\r\n");
        request.append("Host: local\r\n");
        request.append("Connection: Close\r\n");
        request.append("\r\n");

        send_data(socket, request);

        QByteArray response(std::move(read_data(socket)));
        qInfo() << "Response:" << response.length() << "bytes";
        qInfo() << "Response:" << response;

        socket.waitForDisconnected();
        qInfo() << "Done";
    } else {
        qCritical() << socket.errorString();
    }

    return app.exec();
}