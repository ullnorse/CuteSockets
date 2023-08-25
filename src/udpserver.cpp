#include "udpserver.h"

#include <QDebug>
#include <QNetworkDatagram>

UdpServer::UdpServer(QObject *parent)
    : QObject{parent},
    m_socket(new QUdpSocket(this))
{
    connect(m_socket, &QUdpSocket::readyRead, this, &UdpServer::handleReadyRead);
}

bool UdpServer::startServer(const QString &address, quint16 port)
{
    if (m_socket->bind(QHostAddress(address), port))
    {
        qDebug() << "UdpServer: Successfully listening on address:" << address << ":" << port;
        emit startedListening();
        return true;
    }
    else
    {
        qDebug() << "UdpServer: Could not start listening";
        return false;
    }
}

void UdpServer::stopServer()
{
    m_socket->close();
    emit stoppedListening();
}

void UdpServer::sendMessage(const QString &message, const QString &address, quint16 port)
{
    auto socket = std::make_unique<QUdpSocket>();

    socket->connectToHost(QHostAddress(address), port);
    socket->writeDatagram(QNetworkDatagram(message.toUtf8()));
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
