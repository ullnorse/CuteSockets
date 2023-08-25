#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QTcpSocket* client READ client WRITE setClient NOTIFY clientChanged FINAL)
public:
    explicit TcpServer(QObject *parent = nullptr);

    Q_INVOKABLE bool startServer(const QString &address, quint16 port);
    Q_INVOKABLE void stopServer();
    Q_INVOKABLE void disconnectClient();
    Q_INVOKABLE QString clientAddress();
    Q_INVOKABLE void sendMessageToClient(const QString &message);

signals:
    void startedListening();
    void stoppedListening();
    void clientConnected(const QString &address);
    void dataReceived(const QByteArray &data);
    void clientDisconnected();
    void serverClosedClientConnection();

    void clientChanged();

private slots:
    void handleNewConnection();
    void handleClientDisconnected();
    void handleDataFromClient();

private:
    QTcpSocket* client() const;
    void setClient(QTcpSocket *socket);

private:
    QTcpServer *m_server;
    QTcpSocket* m_client = nullptr;
};

#endif // TCPSERVER_H
