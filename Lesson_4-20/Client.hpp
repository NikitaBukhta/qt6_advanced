#ifndef QT6_ADVANCE_LESSON_4_20_CLIENT_HPP
#define QT6_ADVANCE_LESSON_4_20_CLIENT_HPP

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>

namespace lesson_4_20 {

class Client : public QObject{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    ~Client(void);

public slots:
    void connect_to_host(const QString &host, quint16 port);
    void disconnect(void);

private slots:
    void connected(void);
    void disconnected(void);
    void error_occured(QAbstractSocket::SocketError socket_error);
    void state_changed(QAbstractSocket::SocketState socket_state);
    void ready_read(void);

private:
    QTcpSocket m_tcp_socket;
};

}   // !lesson_4_20;

#endif  // !QT6_ADVANCE_LESSON_4_20_CLIENT_HPP;