#ifndef QT6_ADVANCE_LESSON_3_6_TEST_HPP
#define QT6_ADVANCE_LESSON_3_6_TEST_HPP

#include <QObject>
#include <QTimer>

namespace lesson_3_6{

class Test : public QObject{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);
    ~Test(void) override = default;

public slots:
    void run(void);

private:
    void timeout(void);

private:
    QTimer m_timer;
};

}   // !lesson_3_6;

#endif  // !QT6_ADVANCE_LESSON_3_6_TEST_HPP;