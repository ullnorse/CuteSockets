#ifndef APP_H
#define APP_H

#include <QObject>
#include <QQmlApplicationEngine>

#include "tcpserver.h"
#include "tcpclient.h"
#include "udpserver.h"

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = nullptr);

    void init();

private:
    QQmlApplicationEngine *m_mainWindowEngine;
    TcpServer *m_tcpServer;
    TcpClient *m_tcpClient;
    UdpServer *m_udpServer;
};

#endif // APP_H
