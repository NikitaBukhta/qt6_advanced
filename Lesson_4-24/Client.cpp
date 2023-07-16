/* Lesson description;
 *
 * What:
 * Asynchronous TCP;
 * 
 * Why:
 * This is how you would typically work with it;
 * 
 * How:
 * Signals and slots.
 * Note this blocks in the slots;
 */

#include "Client.hpp"

#include <QDebug>
#include <QThread>
#include <QByteArray>
#include <QMetaEnum>

namespace lesson_4_24 {

Client::Client(QObject *parent) 
    : QObject(parent)
{
    connect(&m_socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&m_socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(&m_socket, &QTcpSocket::errorOccurred, this, &Client::error_occured);
    connect(&m_socket, &QTcpSocket::stateChanged, this, &Client::state_changed);
    connect(&m_socket, &QTcpSocket::readyRead, this, &Client::ready_read);
}

Client::~Client(void) {
    disconnect();
}

void Client::connect_to_host(QString host, quint16 port) {
    qInfo() << Q_FUNC_INFO << "called. Current thread:" << QThread::currentThread();

    if (m_socket.isOpen()) {
        disconnect();
    }

    m_socket.connectToHost(host, port);
}

void Client::disconnect(void) {
    qInfo() << Q_FUNC_INFO << "called. Current thread:" << QThread::currentThread();
    m_socket.close();
}

void Client::connected(void) {
    qInfo() << Q_FUNC_INFO << "called. Current thread:" << QThread::currentThread();

    QByteArray data("HELLO\r\n");

    qInfo() <<  Q_FUNC_INFO << "Sending message:" << data.data();

    m_socket.write(data);
}

void Client::disconnected(void) {
    qInfo() << Q_FUNC_INFO << "called. Current thread:" << QThread::currentThread();
}

void Client::error_occured(QAbstractSocket::SocketError socket_error) {
    qInfo() << Q_FUNC_INFO << "called. Current thread:" << QThread::currentThread();

    qInfo() << Q_FUNC_INFO << "error #" << socket_error << ":" << m_socket.errorString();
}

void Client::state_changed(QAbstractSocket::SocketState socket_state) {
    qInfo() << Q_FUNC_INFO << "called. Current thread:" << QThread::currentThread();

    QMetaEnum meta_enum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    
    qInfo() << Q_FUNC_INFO << "state changed to" << meta_enum.valueToKey(socket_state);
}

void Client::ready_read(void) {
    qInfo() << Q_FUNC_INFO << "called. Current thread:" << QThread::currentThread();
    qInfo() << Q_FUNC_INFO << "data from:" << sender() << "bytes" << m_socket.bytesAvailable()
        << "data:" << m_socket.readAll();
}

}   // !lesson_4_24;