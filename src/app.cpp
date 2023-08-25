#include "app.h"

#include <QQmlEngine>

App::App(QObject *parent)
    : QObject{parent},
    m_mainWindowEngine(new QQmlApplicationEngine(this)),
    m_tcpServer(new TcpServer(this)),
    m_tcpClient(new TcpClient(this)),
    m_udpServer(new UdpServer(this))
{
    qmlRegisterSingletonInstance("TcpServer", 1, 0, "TcpServer", m_tcpServer);
    qmlRegisterSingletonInstance("TcpClient", 1, 0, "TcpClient", m_tcpClient);
    qmlRegisterSingletonInstance("UdpServer", 1, 0, "UdpServer", m_udpServer);
}

void App::init()
{
    m_mainWindowEngine->loadFromModule("CuteSockets", "Main");
}
