#ifndef QT6_ADVANCE_LESSON_4_21_CLIENT_HPP
#define QT6_ADVANCE_LESSON_4_21_CLIENT_HPP

#include <QObject>
#include <QString>
#include <QAbstractSocket>
#include <QSslSocket>

namespace lesson_4_21 {

class Client : public QObject{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    ~Client(void);

public slots:
    void connect_to_host(QString host, quint16 port);
    void disconnect(void);

// private slots:
//     void connected(void);
//     void disconnected(void)
    //void error_occured(QAbstractSocket::SocketError socket_error);

private:
    QSslSocket m_ssl_socket;
};

}   // !lesson_4_21;

#endif  // !QT6_ADVANCE_LESSON_4_21_CLIENT_HPP;