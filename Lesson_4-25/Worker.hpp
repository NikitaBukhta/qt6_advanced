#ifndef QT6_ADVANCE_LESSON_4_25_WORKER_HPP
#define QT6_ADVANCE_LESSON_4_25_WORKER_HPP

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

namespace lesson_4_25 {

class Worker : public QObject{
public:
    explicit Worker(QObject *parent = nullptr);
    virtual ~Worker(void);

public slots:
    void start(void);
    void stop(void);
    void timeout(void);
    void ready_read(void);
    void broadcast(void);

private:
    QUdpSocket m_socket;
    quint16 m_PORT = 2020;  // Note < 1024 thoso admin ports / special services. HTTP, FTP, POP3, SMTP;
    QTimer m_timer;
};

}   // !lesson_4_25;

#endif  // !QT6_ADVANCE_LESSON_4_25_WORKER_HPP;