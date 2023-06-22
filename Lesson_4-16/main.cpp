/* Lesson description:
 *
 * What:
 * Network interfaces and addresses;
 * 
 * Why:
 * We can have more than one!
 * 
 * How:
 * QHostAddress;
 */

#include <QCoreApplication>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>

QString toQString(const QAbstractSocket::NetworkLayerProtocol socket){
    switch (socket) {
    case QAbstractSocket::UnknownNetworkLayerProtocol:
        return QString("unknown");
    case QAbstractSocket::AnyIPProtocol:
        return QString("Any");
    case QAbstractSocket::IPv4Protocol:
        return QString("IPv4");
    case QAbstractSocket::IPv6Protocol:
        return QString("IPv6");
    }

    return {};
}

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    for (const auto &address : list) {
        qInfo() << address.toString();

        // Never goes on the Network;
        qInfo() << "\t Loopback:" << address.isLoopback();

        // Send to many;
        qInfo() << "\t Multicast:" << address.isMulticast();

        qInfo() << "\t Protocol: " << toQString(address.protocol());
    }

    return app.exec();
}