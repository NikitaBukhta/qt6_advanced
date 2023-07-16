#include "Worker.hpp"

#include <QDebug>
#include <QThread>
#include <QString>
#include <QDateTime>
#include <QByteArray>
#include <QNetworkDatagram>

#define LOG_FUNC_INFO qInfo() << Q_FUNC_INFO << "called on thread:" << QThread::currentThread();

namespace lesson_4_27 {

Worker::Worker(QObject *parent) 
    : QObject(parent)
{
    LOG_FUNC_INFO;
}

Worker::~Worker(void) {
    LOG_FUNC_INFO

    stop();
}

void Worker::start(void) {
    LOG_FUNC_INFO;

    m_socket = new QUdpSocket(this);
    m_timer = new QTimer(this);
    m_loop = new QEventLoop(this);

    init();

    if (!m_socket->bind(m_PORT)) {
        qCritical() << Q_FUNC_INFO << m_socket->errorString();
        return;
    }

    qInfo() << Q_FUNC_INFO << "work with " << m_socket->localAddress()
        << ":" << m_socket->localPort();

    broadcast();

    m_loop->exec();  // block;
}

void Worker::stop(void) {
    LOG_FUNC_INFO;

    m_timer->stop();
    m_socket->close();

    if (m_loop) {
        qInfo() << Q_FUNC_INFO << "stop loop";
        m_loop->quit();
        delete m_loop;
    }

    deleteLater();
}

void Worker::timeout(void) {
    LOG_FUNC_INFO;

    QString date(QDateTime::currentDateTime().toString());
    QByteArray data(date.toLatin1());

    qInfo() << Q_FUNC_INFO << "sending data:" << data;

    QNetworkDatagram data_transfered(data, QHostAddress::Broadcast, m_PORT);
    m_socket->writeDatagram(data_transfered);

    if (++m_loop_counter >= m_LOOP_MAX) {
        stop();
    }
}

void Worker::ready_read(void) {
    LOG_FUNC_INFO;
    QNetworkDatagram received_data;

    while(m_socket->hasPendingDatagrams()) {
        received_data = std::move(m_socket->receiveDatagram());
        qDebug() << Q_FUNC_INFO << "data:" << received_data.data();
    }
}

void Worker::broadcast(void) {
    LOG_FUNC_INFO;

    m_timer->start();
}

void Worker::init(void) {
    LOG_FUNC_INFO;

    connect(m_timer, &QTimer::timeout, this, &Worker::timeout);
    connect(m_socket, &QUdpSocket::readyRead, this, &Worker::ready_read);
    
    m_timer->setInterval(1000);
}

}   // !lesson_4_27;