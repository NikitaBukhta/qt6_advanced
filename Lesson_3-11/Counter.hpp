#ifndef QT6_ADVANCED_LESSON_3_11_COUNTER_HPP
#define QT6_ADVANCED_LESSON_3_11_COUNTER_HPP

#include <QMutex>
#include <QRunnable>

namespace lesson_3_11 {

class Counter : public QRunnable {
public:
    Counter(QMutex *mutex, qint32 *counter);
    virtual ~Counter(void);

    // Overriding QRunnable starts;

    virtual void run(void) override;

    // Overriding QRunnable ends;

private:
    QMutex *m_mutex;
    qint32 *m_counter;
};

}   // !lesson_3_11;

#endif  // !QT6_ADVANCED_LESSON_3_11_COUNTER_HPP;