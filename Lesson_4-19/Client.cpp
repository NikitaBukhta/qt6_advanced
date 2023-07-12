#include "Client.hpp"

#include <QDebug>
#include <QMetaEnum>

namespace lesson_4_19 {

Client::Client(QObject *parent) : QObject(parent) {
    connect(&m_tcp_socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&m_tcp_socket, &QTcpSocket::disconnected, this, &Client::disconnected);

    connect(&m_tcp_socket, &QTcpSocket::errorOccurred, this, &Client::error_occured);
    connect(&m_tcp_socket, &QTcpSocket::stateChanged, this, &Client::state_changed);
    connect(&m_tcp_socket, &QTcpSocket::readyRead, this, &Client::ready_read);
}

Client::~Client(void) {
    disconnect();
}

void Client::connect_to_host(const QString &host, quint16 port) {
    if (m_tcp_socket.isOpen()) {
        disconnect();
    }

    qInfo() << "Trying to connect to host:" << host << "on port" << port;

    m_tcp_socket.connectToHost(host, port);
}

void Client::disconnect(void) {
    m_tcp_socket.close();
    m_tcp_socket.waitForDisconnected();
}

void Client::connected(void) {
    qInfo() << "Connected succsessfully!";
    qInfo() << "Sening hello message...";
    m_tcp_socket.write("Hello!\r\n");
}

void Client::disconnected(void) {
    qInfo("Disconnected!");
}

void Client::error_occured(QAbstractSocket::SocketError socket_error) {
    qCritical() << "Error:" << socket_error << ":" << m_tcp_socket.errorString();
}

void Client::state_changed(QAbstractSocket::SocketState socket_state) {
    QMetaEnum meta_enum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qInfo() << "State:" << meta_enum.valueToKey(socket_state);
}

void Client::ready_read(void) {
    qInfo() << "Dtat from:" << sender() << "bytes:" << m_tcp_socket.bytesAvailable();
    qInfo() << "Data:" << m_tcp_socket.readAll();
}

}   // !lesson_4_19;