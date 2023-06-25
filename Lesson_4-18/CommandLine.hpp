#ifndef QT6_ADVANCE_LESSON_4_18_COMMANDLINE_HPP
#define QT6_ADVANCE_LESSON_4_18_COMMANDLINE_HPP

#include <QObject>
#include <QTextStream>
#include <QFile>

namespace lesson_4_18 {

class CommandLine : public QObject {
    Q_OBJECT

public:
    explicit CommandLine(QObject *parent = nullptr, FILE *file_handler = nullptr);
    ~CommandLine(void) = default;

    [[noreturn]] void monitor(void);

signals:
    void command(QString value);

private:
    QTextStream m_cin;
};

}   // !lesson_4_18;

#endif  // !QT6_ADVANCE_LESSON_4_18_COMMANDLINE_HPP;