#include "appmanager.h"

#include <QQmlEngine>

AppManager::AppManager(QObject *parent)
    : QObject{parent},
    m_server(new TcpServer(this)),
    m_client(new TcpClient(this))
{
    registerTypes();
}

void AppManager::registerTypes()
{
    qmlRegisterSingletonType<TcpServer>("TcpServer", 1, 0, "TcpServer",
        [&](QQmlEngine*, QJSEngine*) -> QObject* {
            return m_server;
        }
    );

    qmlRegisterSingletonType<TcpClient>("TcpClient", 1, 0, "TcpClient",
        [&](QQmlEngine*, QJSEngine*) -> QObject* {
            return m_client;
        }
    );
}
