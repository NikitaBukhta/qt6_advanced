#ifndef QT6_ADVANCE_LESSON_4_24_CLIENT_HPP
#define QT6_ADVANCE_LESSON_4_24_CLIENT_HPP

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QAbstractSocket>

namespace lesson_4_24 {

class Client : public QObject{
public:
    Client(QObject *parent = nullptr);
    virtual ~Client(void);

public slots:
    void connect_to_host(QString host, quint16 port);
    void disconnect(void);

private slots:
    void connected(void);
    void disconnected(void);
    void error_occured(QAbstractSocket::SocketError socket_error);
    void state_changed(QAbstractSocket::SocketState socket_state);
    void ready_read(void);

private:
    QTcpSocket m_socket;
};

}   // !lesson_4_24;

#endif  // !QT6_ADVANCE_LESSON_4_24_CLIENT_HPP;