#ifndef QT6_ADVANCED_LESSON_4_26_CLIENT_HPP
#define QT6_ADVANCED_LESSON_4_26_CLIENT_HPP

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QAbstractSocket>

namespace lesson_4_26 {

class Client : public QObject {
public:
    explicit Client(QObject *parent = nullptr);
    virtual ~Client(void);

    const QString& host(void) const;
    void set_host(const QString &val);

    quint16 port(void) const;
    void set_port(quint16 val);

public slots:
    void disconnect(void);
    void run(void);

private slots:
    void connected(void);
    void disconnected(void);
    void error_occured(QAbstractSocket::SocketError socket_error);
    void state_changed(QAbstractSocket::SocketState m_socket_state);
    void ready_read(void);

private:
    void init(void);
    void connect_to_host(void);

private:
    QTcpSocket *m_socket;
    QString m_host;
    quint16 m_port;
};

}   // !lesson_4_26;

#endif  // !QT6_ADVANCED_LESSON_4_26_CLIENT_HPP;