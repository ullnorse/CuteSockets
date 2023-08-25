#include "tcpserver.h"

#include <QDebug>

TcpServer::TcpServer(QObject *parent)
    : QObject{parent},
    m_server(new QTcpServer(this))
{
    connect(m_server, &QTcpServer::newConnection, this, &TcpServer::handleNewConnection);
}

bool TcpServer::startServer(const QString &address, quint16 port)
{
    if (m_server->listen(QHostAddress(address), port))
    {
        emit startedListening();
        qDebug() << "TcpServer: Listening on address:" << address << ":" << port;
        return true;
    }
    else
    {
        qDebug() << "TcpServer: Could not start listening";
        return false;
    }
}

void TcpServer::stopServer()
{
    if (m_client)
    {
        m_client->deleteLater();
    }

    m_server->close();

    emit stoppedListening();

    qDebug() << "TcpServer: Stopped listening";
}

void TcpServer::disconnectClient()
{
    if (m_client)
    {
        m_client->disconnectFromHost();
        delete m_client;
        setClient(nullptr);
        emit serverClosedClientConnection();
    }
}

QString TcpServer::clientAddress()
{
    if (m_client)
    {
        return m_client->peerAddress().toString();
    }

    return "";
}

void TcpServer::sendMessageToClient(const QString &message)
{
    if (m_client)
    {
        m_client->write(qPrintable(message));
    }
}

void TcpServer::handleNewConnection()
{
    if (!m_client)
    {
        QTcpSocket *client = m_server->nextPendingConnection();

        if (client)
        {
            connect(client, &QTcpSocket::disconnected, this, &TcpServer::handleClientDisconnected);
            connect(client, &QTcpSocket::readyRead, this, &TcpServer::handleDataFromClient);

            setClient(client);

            emit clientConnected(client->peerAddress().toString());

            qDebug() << "TcpServer: New client connected";
        }
    }
    else
    {
        QTcpSocket *client = m_server->nextPendingConnection();
        client->disconnectFromHost();
        client->deleteLater();
        qDebug() << "TcpServer: Rejected additional connection";
    }
}

void TcpServer::handleClientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());

    if (client)
    {
        qDebug() << "TcpServer: Client disconnected:" << client->peerAddress().toString();

        client->deleteLater();
        setClient(nullptr);

        emit clientDisconnected();
    }
}

void TcpServer::handleDataFromClient()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    if (socket)
    {
        QByteArray data = socket->readAll();

        qDebug() << "TcpServer: Received data:" << data;

        emit dataReceived(data);
    }
}

QTcpSocket* TcpServer::client() const {
    return m_client;
}

void TcpServer::setClient(QTcpSocket *socket)
{
    if (m_client != socket)
    {
        m_client = socket;
        emit clientChanged();
    }
}
