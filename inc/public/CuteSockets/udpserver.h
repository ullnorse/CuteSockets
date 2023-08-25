#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(QObject *parent = nullptr);

    Q_INVOKABLE void startServer(const QString &address, quint16 port);
    Q_INVOKABLE void stopServer();
    Q_INVOKABLE void sendMessage(const QString &message, const QString &address, quint16 port);

signals:
    void startedListening();
    void stoppedListening();
    void clientConnected(const QString &address);
    void dataReceived(const QString &data);

private slots:
    void handleReadyRead();

private:
    QUdpSocket *m_socket;
};

#endif // UDPSERVER_H
