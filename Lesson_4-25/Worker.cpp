#include "Worker.hpp"

#include <QThread>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QByteArray>
#include <QNetworkDatagram>

#define LOG_FUNC_INFO qInfo() << Q_FUNC_INFO << "called on thread:" << QThread::currentThread();

namespace lesson_4_25 {
    
Worker::Worker(QObject *parent)
    : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &Worker::timeout);
    connect(&m_socket, &QUdpSocket::readyRead, this, &Worker::ready_read);
    
    m_timer.setInterval(1000);
}

Worker::~Worker(void) {
    stop();
}

void Worker::start(void) {
    LOG_FUNC_INFO

    if(!m_socket.bind(m_PORT)) {
        qCritical() << Q_FUNC_INFO << m_socket.errorString();
        return;
    }

    qInfo() << Q_FUNC_INFO << "Started UDP on" 
        << m_socket.localAddress() << ":" << m_socket.localPort();

    broadcast();
}

void Worker::stop(void) {
    LOG_FUNC_INFO;

    m_timer.stop();
    m_socket.close();
}

void Worker::timeout(void) {
    LOG_FUNC_INFO;

    QString date(QDateTime::currentDateTime().toString());
    QByteArray transfer_data(date.toLatin1());

    qInfo() << Q_FUNC_INFO << "data send:" << transfer_data;

    QNetworkDatagram datagram(transfer_data, QHostAddress::Broadcast, m_PORT);
    m_socket.writeDatagram(datagram);
}

void Worker::ready_read(void) {
    LOG_FUNC_INFO;

    QNetworkDatagram received_data;
    while(m_socket.hasPendingDatagrams()) {
        received_data = std::move(m_socket.receiveDatagram());
        qDebug() << Q_FUNC_INFO << "Read" << received_data.data() << "from" 
            << received_data.senderAddress() << ":" 
            << received_data.senderPort();
    }
}

void Worker::broadcast(void) {
    LOG_FUNC_INFO
    m_timer.start();
}

}   // !lesson_4_25;