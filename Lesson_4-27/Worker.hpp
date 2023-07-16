#ifndef QT6_ADNVACED_LESSON_4_27_WORKER_HPP
#define QT6_ADNVACED_LESSON_4_27_WORKER_HPP

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QEventLoop>

namespace lesson_4_27 {

class Worker : public QObject {
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
    void init(void);

private:
    QUdpSocket *m_socket;
    quint16 m_PORT = 2020;
    QTimer *m_timer;

    QEventLoop *m_loop;
    quint16 m_loop_counter;
    const quint16 m_LOOP_MAX = 3;
};

}   // !lesson_4_27;

#endif  // !QT6_ADNVACED_LESSON_4_27_WORKER_HPP;