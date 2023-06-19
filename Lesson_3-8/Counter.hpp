#ifndef QT6_ADNVANCE_LESSON_3_8_COUNTER_HPP
#define QT6_ADNVANCE_LESSON_3_8_COUNTER_HPP

#include <QObject>

namespace lesson_3_8 {

class Counter : public QObject{
    Q_OBJECT

public:
    explicit Counter(QObject *parent = nullptr);
    ~Counter(void);

signals:

public slots:
    void start(void);
};

}   // !lesson_3_8;

#endif  // !QT6_ADNVANCE_LESSON_3_8_COUNTER_HPP;