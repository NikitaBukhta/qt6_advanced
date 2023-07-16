#include "Client.hpp"

#include <QDebug>
#include <QThread>
#include <QMetaEnum>
#include <QByteArray>

#define LOG_FUNC_INFO qInfo() << Q_FUNC_INFO << "called on thread:" << QThread::currentThread();

namespace lesson_4_26 {

Client::Client(QObject *parent)
    : QObject(parent)
    , m_port(0)
{
    LOG_FUNC_INFO;
}

Client::~Client(void) {
    LOG_FUNC_INFO;
}

const QString& Client::host(void) const {
    return m_host;
}

void Client::set_host(const QString &val) {
    m_host = val;
}

quint16 Client::port(void) const {
    return m_port;
}

void Client::set_port(quint16 val) {
    m_port = val;
}

void Client::disconnect(void) {
    LOG_FUNC_INFO;
    m_socket->close();
}

void Client::run(void) {
    LOG_FUNC_INFO;

    m_socket = new QTcpSocket(this);
    init();
    connect_to_host();

    m_socket->waitForDisconnected();
    qInfo() << Q_FUNC_INFO << "finished run method!";
    deleteLater();
}

void Client::connected(void) {
    LOG_FUNC_INFO;
    m_socket->write("HELLO\r\n");
}

void Client::disconnected(void) {
    LOG_FUNC_INFO;
}

void Client::error_occured(QAbstractSocket::SocketError socket_error) {
    LOG_FUNC_INFO;
    qCritical() << Q_FUNC_INFO << "error:" << socket_error 
        << "description:" << m_socket->errorString();
}

void Client::state_changed(QAbstractSocket::SocketState state) {
    LOG_FUNC_INFO;

    QMetaEnum meta_enum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qInfo() << Q_FUNC_INFO << "state:" << meta_enum.valueToKey(state);
}

void Client::ready_read(void) {
    LOG_FUNC_INFO;

    qint64 bytes_available = m_socket->bytesAvailable();
    QByteArray data = m_socket->readAll();

    qInfo() << Q_FUNC_INFO << "sender:" << sender() << "bytes:" << m_socket->bytesAvailable()
        << "data:" << data;

    qDebug() << Q_FUNC_INFO << bool(bytes_available == data.size());
}

void Client::init(void) {
    LOG_FUNC_INFO;

    connect(m_socket, &QTcpSocket::connected, this, &Client::connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(m_socket, &QTcpSocket::errorOccurred, this, &Client::error_occured);
    connect(m_socket, &QTcpSocket::stateChanged, this, &Client::state_changed);
    connect(m_socket, &QTcpSocket::readyRead, this, &Client::ready_read);
}

void Client::connect_to_host(void) {
    LOG_FUNC_INFO;

    if (m_socket->isOpen()) {
        disconnect();
    }

    m_socket->connectToHost(m_host, m_port);
}

}   // !lesson_4_26;