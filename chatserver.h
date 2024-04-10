#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class ChatServer : public QObject
{
    Q_OBJECT

public:
    ChatServer(QObject *parent = nullptr);
    void startServer(quint16 port);

signals:
    void newMessage(const QString &message);

public slots:
    void onNewConnection();
    void onSocketReadyRead();

private:
    QTcpServer *tcpServer;
    QList<QTcpSocket *> clients;
};

#endif // CHATSERVER_H
