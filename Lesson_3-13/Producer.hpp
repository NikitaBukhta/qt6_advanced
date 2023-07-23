#ifndef QT6_ADVANCED_LESSON_3_13_PRODUCER_HPP
#define QT6_ADVANCED_LESSON_3_13_PRODUCER_HPP

#include <QObject>
#include <QMutex>
#include <QWaitCondition>

namespace lesson_3_13 {

class Producer : public QObject{
    Q_OBJECT

public:
    explicit Producer();

private:
    QMutex &m_mutex;
    QWaitCondition &m_value_ready;
};

}   // !lesson_3_13;

#endif  // !QT6_ADVANCED_LESSON_3_13_PRODUCER_HPP;