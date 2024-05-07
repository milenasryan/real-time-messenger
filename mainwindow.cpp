#include "mainwindow.h"

#include <QDebug>

#include "encryptor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), chatServer(new ChatServer(this)), tcpSocket(new QTcpSocket(this))
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    textEditMessages = new QTextEdit(centralWidget);
    textEditMessages->setReadOnly(true);

    lineEditMessage = new QLineEdit(centralWidget);

    pushButtonSend = new QPushButton("Send", centralWidget);

    connect(pushButtonSend, &QPushButton::clicked, this, &MainWindow::onSendMessage);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(textEditMessages);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(lineEditMessage);
    inputLayout->addWidget(pushButtonSend);

    mainLayout->addLayout(inputLayout);
    centralWidget->setLayout(mainLayout);

    connect(tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::readSocketData);
    connect(chatServer, &ChatServer::newMessage, this, &MainWindow::displayServerMessage);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred), this, &MainWindow::displayError);

    chatServer->startServer(12345);

    tcpSocket->connectToHost(QHostAddress::LocalHost, 12345);
}

void MainWindow::setUsername(const QString &username) {
    this->username = username;
}

void MainWindow::onSendMessage() {
    Encryptor encryptor;
    QString message = lineEditMessage->text().trimmed();
    if (!message.isEmpty()) {
        QString fullMessage = username + ": " + message;
        QString encryptedMessage = encryptor.encrypt(fullMessage);

        QByteArray data = encryptedMessage.toUtf8();
        tcpSocket->write(data);
        textEditMessages->append(fullMessage);
        lineEditMessage->clear();
    }
}

void MainWindow::displayServerMessage(const QString &message) {
    Encryptor encryptor;
    QString decryptedMessage = encryptor.decrypt(message);
    textEditMessages->append(decryptedMessage);
}


void MainWindow::readSocketData()
{
    QByteArray data = tcpSocket->readAll();
    displayServerMessage(QString::fromUtf8(data));
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);

    qDebug() << "Socket Error:" << tcpSocket->errorString();

    textEditMessages->append("Error: " + tcpSocket->errorString());
}
