#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>

#include "Controllers/tcpserver.h"
#include "Controllers/tcpclient.h"
#include "Controllers/udpserver.h"

class AppManager : public QObject
{
    Q_OBJECT
public:
    explicit AppManager(QObject *parent = nullptr);

signals:

private:
    void registerTypes();

private:
    TcpServer *m_tcpServer;
    TcpClient *m_tcpClient;
    UdpServer *m_udpServer;
};

#endif // APPMANAGER_H
