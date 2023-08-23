#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent)
    : QObject{parent},
    m_socket(new QTcpSocket(this))
{
    connect(m_socket, &QTcpSocket::connected, this, [this](){
        setConnected(true);
        emit connectedToServer();
    });

    connect(m_socket, &QTcpSocket::disconnected, this, [this](){
        setConnected(false);
        emit disconnectedFromServer();
    });

    connect(m_socket, &QTcpSocket::errorOccurred, this, [this](){
        emit errorOccured();
    });

    connect(m_socket, &QTcpSocket::readyRead, this, [this]{
        QByteArray data = m_socket->readAll();
        emit dataReceived(data);
    });
}

void TcpClient::connectToServer(const QString &address, quint16 port)
{
    m_socket->connectToHost(QHostAddress(address), port);
}

void TcpClient::disconnectFromServer()
{
    m_socket->disconnectFromHost();
}

bool TcpClient::connected() const
{
    return m_connected;
}

void TcpClient::setConnected(bool state)
{
    if (m_connected != state)
    {
        m_connected = state;
        emit connectedChanged();
    }
}
