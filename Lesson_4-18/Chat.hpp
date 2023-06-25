#ifndef QT6_ADVANCE_LESSON_4_18_CHAT_HPP
#define QT6_ADVANCE_LESSON_4_18_CHAT_HPP

#include <QObject>
#include <QString>
#include <QUdpSocket>

namespace lesson_4_18 {

class Chat : public QObject{
    Q_OBJECT

public:
    explicit Chat(QObject *parent = nullptr);
    ~Chat(void);

public slots:
    void command(QString value);
    void send(QString value);
    void ready_read(void);

private:
    QString m_name;
    QUdpSocket m_udp_socket;
    const quint16 m_PORT;
};

}   // !lesson_4_18;

#endif  // !QT6_ADVANCE_LESSON_4_18_CHAT_HPP;