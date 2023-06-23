#ifndef QT6_ADVANCE_LESSON_4_17_WORKER_HPP
#define QT6_ADVANCE_LESSON_4_17_WORKER_HPP

#include <QObject>
#include <QTimer>
#include <QUdpSocket>

namespace lesson_4_17 {

class Worker : public QObject{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker(void);

public slots:
    void start(void);
    void stop(void);
    void timeout(void);
    void ready_read(void);
    void broadcast(void);

private:
    QUdpSocket m_udp_socket;
    QTimer m_timer;
    const quint16 m_PORT;   // Note < 1024 those admin ports / special services. HTTP, FTP, POP3, SMTP;
};

}   // !lesson_4_17;

#endif  // !QT6_ADVANCE_LESSON_4_17_WORKER_HPP;