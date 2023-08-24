#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged FINAL)
public:
    explicit TcpClient(QObject *parent = nullptr);

    Q_INVOKABLE void connectToServer(const QString &address, quint16 port);
    Q_INVOKABLE void disconnectFromServer();
    Q_INVOKABLE void sendMessageToServer(const QString &message);

    bool connected() const;
    void setConnected(bool state);

signals:
    void connectedToServer();
    void disconnectedFromServer();
    void errorOccured();
    void dataReceived(const QByteArray &data);

    void connectedChanged();

private:
    QTcpSocket *m_socket;
    bool m_connected = false;
};

#endif // TCPCLIENT_H
