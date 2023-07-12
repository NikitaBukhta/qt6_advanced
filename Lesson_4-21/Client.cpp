#include "Client.hpp"

namespace lesson_4_21 {

Client::Client(QObject *parent) : QObject(parent) {

}

Client::~Client(void) {
    disconnect();
}

void Client::connect_to_host(QString host, quint16 port) {
    if (m_ssl_socket.isOpen()) {
        disconnect();
    }

    m_ssl_socket.setProtocol(QSsl::SecureProtocols);
    m_ssl_socket.connectToHostEncrypted(host, port);
}

void Client::disconnect(void) {
    m_ssl_socket.close();
    m_ssl_socket.waitForDisconnected();
}

}   // !lesson_4_21;