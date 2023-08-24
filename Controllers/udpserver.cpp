#include "udpserver.h"

#include <QDebug>

UdpServer::UdpServer(QObject *parent)
    : QObject{parent},
    m_socket(new QUdpSocket(this))
{
    connect(m_socket, &QUdpSocket::readyRead, this, &UdpServer::handleReadyRead);
}

void UdpServer::startServer(const QString &address, quint16 port)
{
    if (m_socket->bind(QHostAddress(address), port))
    {
        qDebug() << "UdpServer: Successfully listening on address:" << address << ":" << port;
        emit startedListening();
    }
    else
    {
        qDebug() << "UdpServer: Could not start listening";
    }
}

void UdpServer::stopServer()
{
    m_socket->close();
    emit stoppedListening();
}

void UdpServer::sendMessage(const QString &message, const QString &address, quint16 port)
{
    qDebug() << "msg:" << message << "address:" << address << "port:" << port;
}

void UdpServer::handleReadyRead()
{
    qint64 pendingDatagramSize = m_socket->pendingDatagramSize();

    if (pendingDatagramSize <= 0) {
        return;
    }

    auto datagram = std::make_unique<char[]>(pendingDatagramSize);

    qint64 bytesRead = m_socket->readDatagram(datagram.get(), pendingDatagramSize);

    if (bytesRead > 0) {
        QByteArray byteArray(datagram.get(), bytesRead);
        QString data = QString::fromUtf8(byteArray);

        emit dataReceived(data);
    }
}
