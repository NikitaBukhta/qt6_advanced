#ifndef QT6_ADVANCED_LESSON_3_13_CONSUMER_HPP
#define QT6_ADVANCED_LESSON_3_13_CONSUMER_HPP

#include <QObject>
#include <QMutex>
#include <QWaitCondition>

namespace lesson_3_13 {

class Consumer : public QObject {
    Q_OBJECT;

public:
    explicit Consumer(QMutex &mutex, QWaitCondition &value_ready, qint32 &value, QObject *parent = nullptr);
    virtual ~Consumer(void);

public slots:
    void run(void);

private:
    QMutex &m_mutex;
    QWaitCondition &m_value_ready;
    qint32 &m_value;
};

}   // !lesson_3_13;

#endif  // !QT6_ADVANCED_LESSON_3_13_CONSUMER_HPP;