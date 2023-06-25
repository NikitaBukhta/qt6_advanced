#include "Client.hpp"

#include <QDebug>
#include <QByteArray>
#include <QMetaEnum>
#include <QNetworkProxy>

namespace lesson_4_20 {

Client::Client(QObject *parent) : QObject(parent) {
    static QString function("[Client] [Constructor]");
    qInfo() << function << "called";

    connect(&m_tcp_socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&m_tcp_socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(&m_tcp_socket, &QTcpSocket::errorOccurred, this, &Client::error_occured);
    connect(&m_tcp_socket, &QTcpSocket::stateChanged, this, &Client::state_changed);
    connect(&m_tcp_socket, &QTcpSocket::readyRead, this, &Client::ready_read);

    // Proxy stuff;
    QNetworkProxy proxy(QNetworkProxy::HttpProxy, "173.176.14.246", 3128);    // Canada;

    // Set auth;
    // proxy.setUser("User");
    // proxy.setPassword("pass");

    // App proxy;
    QNetworkProxy::setApplicationProxy(proxy);

    // Per socket;
    m_tcp_socket.setProxy(proxy);
}

Client::~Client(void) {
    static QString function("[Client] [Constructor]");
    qInfo() << function << "called";
    
    if (m_tcp_socket.isOpen()){
        disconnect();
    }
}

void Client::connect_to_host(const QString &host, quint16 port) {
    static QString function("[Client] [connect_to_host]");
    if (m_tcp_socket.isOpen()) {
        disconnect();
    }

    qInfo() << function << "Trying to connect to host" << host << "on port" << port;
    m_tcp_socket.connectToHost(host, port);
}

void Client::disconnect(void) {
    static QString function("[Client] [disconnect]");
    qInfo() << function << "called";

    m_tcp_socket.close();
    m_tcp_socket.waitForDisconnected();
}

void Client::connected(void) {
    static QString function("[Client] [connected]");
    qInfo() << function << "sending some data";
    // socket.write("Hello\r\n");

    QByteArray data;
    data.append("Get /get HTTP/1.1\r\n");
    data.append("User-Agent: Mozilla/4.0 (compitable; MISE 8.0; Windows NT 6.0; Trident/4.0)\r\n");
    data.append("Host: local\r\n");
    data.append("Connection: Close\r\n");
    data.append("\r\n");
    
    m_tcp_socket.write(data);
    m_tcp_socket.waitForBytesWritten();
}

void Client::disconnected(void) {
    static QString function("[Client] [disconnected]");
    qInfo() << function << "called";
}

void Client::error_occured(QAbstractSocket::SocketError socket_error) {
    static QString function("[Client] [error_occured]");
    qCritical() << function << "Error:" << socket_error << m_tcp_socket.errorString();
}

void Client::state_changed(QAbstractSocket::SocketState socket_state) {
    static QString function("[Client] [state_changed]");
    QMetaEnum meta_enum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    
    qInfo() << function << "State:" << meta_enum.valueToKey(socket_state);
}

void Client::ready_read(void) {
    static QString function("[Client] [error_occured]");
    qInfo() << function << "Data from:" << sender() << "bytes:" << m_tcp_socket.bytesAvailable();
    qInfo() << function << "Data:" << m_tcp_socket.readAll();
}

}   // !lesson_4_20;