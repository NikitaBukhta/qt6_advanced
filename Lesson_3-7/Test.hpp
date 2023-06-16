#ifndef QT6_ADVANCE_LESSON_3_7_TEST_HPP
#define QT6_ADVANCE_LESSON_3_7_TEST_HPP

#include <QThread>
#include <QTimer>

namespace lesson_3_7{

class Test : public QThread{
    Q_OBJECT

public:
    explicit Test(QObject *parent = nullptr);
    virtual ~Test(void) override = default;

protected:
    void run(void);

private:
    void test(void);

private:
    QTimer m_timer;
};

}   // !lesson_3_7;

#endif  // !QT6_ADVANCE_LESSON_3_7_TEST_HPP;