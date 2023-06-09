#ifndef QT6_ADVANCE_LESSON_3_10_COUNTER_HPP
#define QT6_ADVANCE_LESSON_3_10_COUNTER_HPP

#include <QRunnable>
#include <QMutex>
#include <QPointer>
#include <QTypeInfo>

namespace lesson_3_10{

class Counter : public QRunnable{
public:
    Counter(QWeakPointer<QMutex> mutex, QWeakPointer<qint32> value);
    ~Counter(void);

    void run(void);
private:
    QSharedPointer<qint32> m_value;
    QSharedPointer<QMutex> m_mutex;
};

};

#endif  // !QT6_ADVANCE_LESSON_3_10_COUNTER_HPP;