#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>

#include "Controllers/tcpserver.h"

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
};

#endif // APPMANAGER_H
