#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), chatServer(new ChatServer(this)), tcpSocket(new QTcpSocket(this))
{
    // Create central widget and set as central widget for MainWindow
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create the UI elements
    textEditMessages = new QTextEdit(centralWidget);
    textEditMessages->setReadOnly(true);

    lineEditMessage = new QLineEdit(centralWidget);

    pushButtonSend = new QPushButton("Send", centralWidget);

    // Connect the button's clicked signal to the appropriate slot
    connect(pushButtonSend, &QPushButton::clicked, this, &MainWindow::onSendMessage);


    // Layouts
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(textEditMessages);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(lineEditMessage);
    inputLayout->addWidget(pushButtonSend);

    mainLayout->addLayout(inputLayout);
    centralWidget->setLayout(mainLayout);

    // Connect the newMessage signal from chatServer to the slot in MainWindow
    connect(tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::readSocketData);
    connect(chatServer, &ChatServer::newMessage, this, &MainWindow::displayServerMessage);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred), this, &MainWindow::displayError);

    // Start the server
    chatServer->startServer(12345); // Use a port number

    // Attempt to connect to the server as a client
    tcpSocket->connectToHost(QHostAddress::LocalHost, 12345);
}

void MainWindow::setUsername(const QString &username) {
    this->username = username; // Set the username
}

void MainWindow::onSendMessage() {
    QString message = lineEditMessage->text().trimmed();
    if (!message.isEmpty()) {
        QString fullMessage = username + ": " + message;
        QByteArray data = fullMessage.toUtf8();

        tcpSocket->write(data); // Send message over the socket

        // Append message to the sender's chat history immediately with their username
        textEditMessages->append(fullMessage);

        lineEditMessage->clear(); // Clear the input field
    }
}

void MainWindow::displayServerMessage(const QString &message) {
    // Display all incoming messages
    textEditMessages->append(message);
}


void MainWindow::readSocketData()
{
    QByteArray data = tcpSocket->readAll();
    displayServerMessage(QString::fromUtf8(data));
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // Use this if you're not directly using the socketError variable

    // Log the error to the console
    qDebug() << "Socket Error:" << tcpSocket->errorString();

    // If you also want to display the error in the UI, you can do so like this:
    textEditMessages->append("Error: " + tcpSocket->errorString());
}
