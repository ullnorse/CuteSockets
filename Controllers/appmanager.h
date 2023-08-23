#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>

#include "Controllers/tcpserver.h"
#include "Controllers/tcpclient.h"

class AppManager : public QObject
{
    Q_OBJECT
public:
    explicit AppManager(QObject *parent = nullptr);

signals:

private:
    void registerTypes();

private:
    TcpServer *m_server;
    TcpClient *m_client;
};

#endif // APPMANAGER_H
