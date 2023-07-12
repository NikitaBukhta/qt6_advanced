#include "Client.hpp"

#include <QCoreApplication>

using namespace lesson_4_21;

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    Client client;
    client.connect_to_host("httpbin.org", 80); // Not encrypted;
    client.connect_to_host("httpbin.org", 443); // SSL - OpenSsl;

    return app.exec();
}