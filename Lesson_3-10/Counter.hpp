#ifndef QT6_ADVANCE_LESSON_3_10_COUNTER_HPP
#define QT6_ADVANCE_LESSON_3_10_COUNTER_HPP

#include <QRunnable>
#include <QMutex>
#include <QPointer>
#include <QTypeInfo>

namespace lesson_3_10{

class Counter : public QRunnable{
public:
    Counter(QMutex *mutex, qint32 *value);
    ~Counter(void);

    // overring QRunnable starts;

    virtual void run(void) override;

    // overring QRunnable ends;
private:
    qint32 *m_value;
    QMutex *m_mutex;
};

};

#endif  // !QT6_ADVANCE_LESSON_3_10_COUNTER_HPP;