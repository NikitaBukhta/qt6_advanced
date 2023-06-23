#include "Worker.hpp"

#include <QDebug>
#include <QDateTime>
#include <QNetworkDatagram>

namespace lesson_4_17 {

Worker::Worker(QObject *parent) 
    : QObject(parent)
    , m_PORT(2020)  // Random port :D;
{
    connect(&m_timer, &QTimer::timeout, this, &Worker::timeout);
    connect(&m_udp_socket, &QUdpSocket::readyRead, this, &Worker::ready_read);
    m_timer.setInterval(5000);
}

Worker::~Worker(void) {
    stop();
}

void Worker::start(void) {
    // QAbstractSocket::ShareAddress;
    if (!m_udp_socket.bind(m_PORT)) {
        qCritical() << m_udp_socket.errorString();
        return;
    }

    qInfo() << "Started UDB on" << m_udp_socket.localAddress() << ":" << m_udp_socket.localPort();

    broadcast();
}

void Worker::stop(void) {
    m_timer.stop();
    m_udp_socket.close();
    qInfo() << "Stopped";
}

void Worker::timeout(void) {
    QString date(QDateTime::currentDateTime().toString());
    QByteArray data(date.toLatin1());

    QNetworkDatagram datargam(data, QHostAddress::Broadcast, m_PORT);
    qInfo() << "Send:" << data;
    m_udp_socket.writeDatagram(datargam);
}

void Worker::ready_read(void) {
    while(m_udp_socket.hasPendingDatagrams()) {
        QNetworkDatagram datagram(m_udp_socket.receiveDatagram());
        qInfo() << "Read:" << datagram.data() << "from" << datagram.senderAddress() << ":" << datagram.senderPort();
    }
}

void Worker::broadcast(void) {
    qInfo() << "Broadcasting...";
    m_timer.start();
}

}   // !lesson_4_17;