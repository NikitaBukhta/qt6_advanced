#ifndef QT6_ADVANCED_LESSON_3_12_WORKER_HPP
#define QT6_ADVANCED_LESSON_3_12_WORKER_HPP

#include <QObject>
#include <QSemaphore>
#include <QList>

namespace lesson_3_12 {

class Worker : public QObject {
public:
    explicit Worker(QSemaphore *sema, QList<qint32> *values, QObject *parent = nullptr);
    ~Worker(void);

public slots:
    void run(void);

private:
    QSemaphore *m_sema;
    QList<qint32> *m_values;
};

}   // !lesson_3_12;

#endif  // !QT6_ADVANCED_LESSON_3_12_WORKER_HPP;