#include "loginwindow.h"

#include "mainwindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    QLabel *titleLabel = new QLabel("Log In", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(15);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel *usernameLabel = new QLabel("Enter username:", this);
    usernameEdit = new QLineEdit(this);

    QLabel *passwordLabel = new QLabel("Enter password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Login", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);

    setLayout(layout);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
}



void LoginWindow::onLoginClicked() {
    emit loginSuccessful(usernameEdit->text());
    this->close();
}

QString LoginWindow::getUsername() {
    return usernameEdit->text();
}
