#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>

#include "tcpserver.h"
#include "tcpclient.h"
#include "udpserver.h"

class AppManager : public QObject
{
    Q_OBJECT
public:
    explicit AppManager(QObject *parent = nullptr);

    Q_INVOKABLE void aboutQt();

signals:

private:
    void registerTypes();

private:
    TcpServer *m_tcpServer;
    TcpClient *m_tcpClient;
    UdpServer *m_udpServer;
};

#endif // APPMANAGER_H
