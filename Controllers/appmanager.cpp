#include "appmanager.h"

#include <QQmlEngine>

AppManager::AppManager(QObject *parent)
    : QObject{parent},
    m_server(new TcpServer(this))
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

    qRegisterMetaType<QTcpSocket*>("QTcpSocket*");
}
