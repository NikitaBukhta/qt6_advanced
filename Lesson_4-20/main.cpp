/* Lesson description:
 *
 * What:
 * Network proxy;
 * 
 * Why:
 * We want to connect to a host via a proxy.
 * Could be a company policy.
 * Maybe we want to mask our identity;
 * 
 * How:
 * QNetworkProxy;
 * 
 * https://free-proxy-list.net/
 */

#include "Client.hpp"

#include <QCoreApplication>

using namespace lesson_4_20;

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    Client client;
    client.connect_to_host("www.httpbin.org", 80);

    return app.exec();
}