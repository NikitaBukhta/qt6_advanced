/* Lesson description:
 *
 * What:
 * Synchronous UDP
 * 
 * Why:
 * We want to use UDP, and block while doing it;
 * 
 * How:
 * Example code;
 */

#include <QCoreApplication>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QString>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QDateTime>

bool bind(QUdpSocket &socket, quint16 port) {
    if (socket.bind(port, QUdpSocket::ShareAddress)) {
        return true;
    }

    qCritical() << "[bind]" << socket.errorString();

    return false;
}

void send(QUdpSocket &socket, quint16 port) {
    qInfo() << "[send]" << "called";

    QString date(QDateTime::currentDateTime().toString());
    QByteArray data(date.toLatin1());

    qDebug() << "[send]" << "sending data by broadcast:" << data;
    QNetworkDatagram datagram(data, QHostAddress::Broadcast, port);

    if (socket.writeDatagram(datagram) <= 0) {
        qCritical() << "[send]" << socket.errorString();
    }
}

void read(QUdpSocket &socket) {
    qInfo() << "[read]" << "called";

    QNetworkDatagram datagram;

    if (!socket.waitForReadyRead(60000)) {
        qWarning() << "[read]" << "Nothing to read!";
        return;
    }

    while (socket.hasPendingDatagrams()) {
        datagram = std::move(socket.receiveDatagram());
        qDebug() << "[read]" << "data read:" << datagram.data();
        datagram.clear();
    }
    
}

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    const quint16 SERVER_PORT = 4569;

    QUdpSocket broadcaster;
    QUdpSocket client;

    qInfo() << "[main]" << "binding sockets";
    if(bind(broadcaster, SERVER_PORT) && bind(client, SERVER_PORT)) {
        send(broadcaster, SERVER_PORT);
        read(client);
    } else {
        qCritical() << "[main]" << "Cannot to bind the sockets";
    }

    return app.exec();
}