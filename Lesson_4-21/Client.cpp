#include "Client.hpp"

#include <QDebug>
#include <QByteArray>
#include <QMetaEnum>

namespace lesson_4_21 {

Client::Client(QObject *parent) : QObject(parent) {
    connect(&m_ssl_socket, &QSslSocket::connected, this, &Client::connected);
    connect(&m_ssl_socket, &QSslSocket::disconnected, this, &Client::disconnected);

    connect(&m_ssl_socket, &QSslSocket::errorOccurred, this, &Client::error_occured);
    connect(&m_ssl_socket, &QSslSocket::stateChanged, this, &Client::state_changed);
    connect(&m_ssl_socket, &QSslSocket::readyRead, this, &Client::ready_read);

    // SSL;
    connect(&m_ssl_socket, &QSslSocket::encrypted, this, &Client::encrypted);
    connect(&m_ssl_socket, &QSslSocket::encryptedBytesWritten, this, &Client::encrypted_bytes_written);
    connect(&m_ssl_socket, &QSslSocket::modeChanged, this, &Client::mode_changed);
    connect(&m_ssl_socket, &QSslSocket::peerVerifyError, this, &Client::peer_verify_error);
    connect(&m_ssl_socket, &QSslSocket::preSharedKeyAuthenticationRequired, this, &Client::pre_shared_key_authentication_required);
    connect(&m_ssl_socket, &QSslSocket::sslErrors, this, &Client::ssl_errors);
}

Client::~Client(void) {
    disconnect();
}

void Client::connect_to_host(QString host, quint16 port) {
    qInfo() << "[Client][connect_to_host]. Host name:"
        << host << "; port" << port;

    if (m_ssl_socket.isOpen()) {
        disconnect();
    }

    m_ssl_socket.setProtocol(QSsl::SecureProtocols);
    m_ssl_socket.connectToHostEncrypted(host, port);
}

void Client::disconnect(void) {
    qInfo() << "[Client][disconnect] called";

    m_ssl_socket.close();
    m_ssl_socket.waitForDisconnected();
}

void Client::connected(void) {
    qInfo() << "[Client][connected] called";
    
    QByteArray data;
    // data.append("Hello\n\r");    // bad request;
    data.append("GET /get HTTP/1.1\r\n");
    data.append("User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0)\r\n");
    data.append("Host: local\r\n");
    data.append("Connection: Close\r\n");
    data.append("\r\n");

    qDebug() << "[Client][connected] data sent:" << data.data();

    m_ssl_socket.write(data);
    m_ssl_socket.waitForBytesWritten();
}

void Client::disconnected(void) {
    qInfo() << "[Client][disconnected] called";
}

void Client::error_occured(QAbstractSocket::SocketError socket_error) {
    qInfo() << "[Client][error_occured] called";
    qCritical() << "[Client][error_occured] error:" << socket_error
        << "-" << m_ssl_socket.errorString();
}

void Client::state_changed(QAbstractSocket::SocketState socket_state) {
    QMetaEnum meta_enum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qInfo() << "[Client][state_changed] socket state changed to" << meta_enum.valueToKey(socket_state);
}

void Client::ready_read(void) {
    qInfo() << "[Client][ready_read] called by" << sender()
        << "count of bytes:" << m_ssl_socket.bytesAvailable();

    QByteArray data = m_ssl_socket.readAll();
    qInfo() << "[Client][ready_read] data:" << data;
}

void Client::encrypted(void) {
    qInfo() << "[Client][encrypted] called";
}

void Client::encrypted_bytes_written(qint64 written) {
    qInfo() << "[Client][encrypted_bytes_written] written:" << written;
}

void Client::mode_changed(QSslSocket::SslMode mode) {
    // Qt does not support this!!! Compile error!
    // QMetaEnum  meta_enum = QMetaEnum::fromType<QSslSocket::SslMode>();
    // qInfo() << "[Client][mode_changed] mode:" << meta_enum.valueToKey(mode);
    qInfo() << "[Client][mode_changed] ssl mode:" << mode;
}

void Client::peer_verify_error(const QSslError &error) {
    qInfo() << "[Client][peer_verify_error] error:" << error.errorString();
}

void Client::pre_shared_key_authentication_required(QSslPreSharedKeyAuthenticator *authenticator) {
    qInfo() << "[Client][pre_shared_key_authentication_required] called";
    // QSslPreSharedKeyAuthenticator lookup if you need;
}

void Client::ssl_errors(const QList<QSslError> &errors) {
    // m_ssl_socket.ignoreSslErrors(); // NOT SECURE;
    qInfo() << "[Client][ssl_errors] count errors:" << errors.count();

    for (const auto &error : errors) {
        qCritical() << "[Client][ssl_errors] error:" << error.errorString();
    }
}

}   // !lesson_4_21;