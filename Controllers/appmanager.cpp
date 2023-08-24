#include "appmanager.h"

#include <QQmlEngine>

AppManager::AppManager(QObject *parent)
    : QObject{parent},
    m_tcpServer(new TcpServer(this)),
    m_tcpClient(new TcpClient(this)),
    m_udpServer(new UdpServer(this))
{
    registerTypes();
}

void AppManager::registerTypes()
{
    qmlRegisterSingletonType<TcpServer>("TcpServer", 1, 0, "TcpServer",
        [&](QQmlEngine*, QJSEngine*) -> QObject* {
        return m_tcpServer;
        }
    );

    qmlRegisterSingletonType<TcpClient>("TcpClient", 1, 0, "TcpClient",
        [&](QQmlEngine*, QJSEngine*) -> QObject* {
        return m_tcpClient;
        }
    );

    qmlRegisterSingletonType<UdpServer>("UdpServer", 1, 0, "UdpServer",
        [&](QQmlEngine*, QJSEngine*) -> QObject* {
            return m_udpServer;
        }
    );
}
