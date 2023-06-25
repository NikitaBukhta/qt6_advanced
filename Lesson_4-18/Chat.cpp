#include "Chat.hpp"
#include "Config.hpp"

#include <QDebug>
#include <QByteArray>
#include <QNetworkDatagram>

namespace lesson_4_18 {

Chat::Chat(QObject *parent) 
    : QObject(parent),
    m_PORT(PORT)
{
    if (m_udp_socket.bind(PORT, QUdpSocket::ShareAddress)) {
        qInfo() << "Started on:" <<  m_udp_socket.localAddress() << ":" << m_udp_socket.localPort();
        connect(&m_udp_socket, &QUdpSocket::readyRead, this, &Chat::ready_read);
    }
}

Chat::~Chat(void) {
    m_udp_socket.close();
}

void Chat::command(QString value) {
    QString message;

    if (m_name.isEmpty()) {
        m_name = value;
        message = m_name + ": joined";
    } else {
        message = m_name + ": " + value;
    }

    send(message);
}

void Chat::send(QString value) {
    QByteArray data = value.toLatin1();
    QNetworkDatagram datagram(data, QHostAddress::Broadcast, m_PORT);

    if (!m_udp_socket.writeDatagram(datagram)) {
        qCritical() << m_udp_socket.errorString();
    }
}

void Chat::ready_read(void) {
    while (m_udp_socket.hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_udp_socket.receiveDatagram();
        qInfo() << datagram.data();
    }
}

}   // !lesson_4_18;