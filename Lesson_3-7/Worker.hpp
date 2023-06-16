#ifndef QT6_ADVANCE_LESSON_3_7_WORKER_HPP
#define QT6_ADVANCE_LESSON_3_7_WORKER_HPP

#include <QObject>

namespace lesson_3_7{

class Worker : public QObject{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr);
    virtual ~Worker(void) override = default;

public slots:
    void work(void);
};

}   // !lesson_3_7;

#endif  // !QT6_ADVANCE_LESSON_3_7_WORKER_HPP;