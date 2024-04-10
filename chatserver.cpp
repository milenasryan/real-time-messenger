#include "chatserver.h"

ChatServer::ChatServer(QObject *parent)
    : QObject(parent), tcpServer(new QTcpServer(this))
{
    connect(tcpServer, &QTcpServer::newConnection, this, &ChatServer::onNewConnection);
}

void ChatServer::startServer(quint16 port)
{
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        // Handle error here if needed
    }
}

void ChatServer::onNewConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    clients.append(clientSocket);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::onSocketReadyRead);
    // You might want to connect other signals like disconnected to remove the client from the list
}

void ChatServer::onSocketReadyRead()
{
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());
    if (senderSocket) {
        const QByteArray data = senderSocket->readAll();
        QString message = QString::fromUtf8(data);
        qDebug() << "Server received message:" << message;

        // Debug: Output the sender and clients info
        qDebug() << "Sender socket pointer:" << senderSocket;
        qDebug() << "Sender address:" << senderSocket->peerAddress().toString();
        qDebug() << "Number of clients:" << clients.size();

        // Broadcast to all clients except the sender
        for (QTcpSocket *client : qAsConst(clients)) {
            qDebug() << "Client socket pointer:" << client;
            qDebug() << "Client address:" << client->peerAddress().toString();
            qDebug() << "Client state:" << client->state();

            if (client->state() == QAbstractSocket::ConnectedState) {
                if (client != senderSocket) {
                    qDebug() << "Broadcasting to client";
                    client->write(data);
                } else {
                    qDebug() << "Not broadcasting to sender";
                }
            } else {
                qDebug() << "Client not connected, not sending";
            }
        }
    } else {
        qDebug() << "Sender socket is null";
    }
}
