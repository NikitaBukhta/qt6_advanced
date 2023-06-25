#include "Chat.hpp"
#include "CommandLine.hpp"
#include "Config.hpp"

#include <QCoreApplication>
#include <QFuture>
#include <QtConcurrent>

using namespace lesson_4_18;

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    
    CommandLine command_line(&app, stdin);
    auto ret = QtConcurrent::run(&CommandLine::monitor, &command_line);

    Chat chat;
    QObject::connect(&command_line, &CommandLine::command, &chat, &Chat::command, Qt::QueuedConnection);

    qInfo() << "Enter your name to begin";

    return app.exec();
}