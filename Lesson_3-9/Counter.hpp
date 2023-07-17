#ifndef QT6_ADVANCED_LESSON_3_9_COUNTER_HPP
#define QT6_ADVANCED_LESSON_3_9_COUNTER_HPP

#include <QRunnable>

namespace lesson_3_9 {

class Counter : public QRunnable {
public:
    Counter(void) = default;
    virtual ~Counter(void) = default;

    // Override QRunnable starts;

    virtual void run(void) override;

    // Override QRunnable ends;
};

}   // !lesson_3_9;

#endif  // !QT6_ADVANCED_LESSON_3_9_COUNTER_HPP;