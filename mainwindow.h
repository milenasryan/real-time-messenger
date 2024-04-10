#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "chatserver.h"
#include <QTcpSocket>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setUsername(const QString &username);

private slots:
    void onSendMessage();
    void displayServerMessage(const QString &message);
    void readSocketData();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QTextEdit *textEditMessages;
    QLineEdit *lineEditMessage;
    QPushButton *pushButtonSend;
    ChatServer *chatServer;
    QTcpSocket *tcpSocket;
    QString username;
};

#endif // MAINWINDOW_H
