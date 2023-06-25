#include "CommandLine.hpp"

namespace lesson_4_18 {

CommandLine::CommandLine(QObject *parent, FILE *file_handler)
    : QObject(parent)
    , m_cin(file_handler)
{

}

void CommandLine::monitor(void) {
    while (true) {
        QString value = m_cin.readLine();
        emit command(value);
    }
}

}   // !lesson_4_18;