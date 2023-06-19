#ifndef QT6_ADVANCE_LESSON_3_8_MANAGER_HPP
#define QT6_ADVANCE_LESSON_3_8_MANAGER_HPP

#include <QObject>
#include <QList>
#include <QThread>

namespace lesson_3_8 {

class Manager : public QObject {
    Q_OBJECT

public:
    explicit Manager(QObject *parent = nullptr);
    
    void start(void);

public slots:
    void started(void);
    void finished(void);

private:
    QList<QThread*> m_threads;
};

}   // !lesson_3_8;

#endif  // !QT6_ADVANCE_LESSON_3_8_MANAGER_HPP;