#include "loginwindow.h"
#include "mainwindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    // Create title label with a larger font
    QLabel *titleLabel = new QLabel("Log In", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(15); // Set the font size as desired
    titleFont.setBold(true); // Make the font bold
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter); // Center align the text

    // Initialize login widgets
    QLabel *usernameLabel = new QLabel("Enter username:", this);
    usernameEdit = new QLineEdit(this);

    QLabel *passwordLabel = new QLabel("Enter password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Login", this);

    // Layout the login widgets
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel); // Add the title label to the layout
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);

    setLayout(layout);

    // Connect the login button signal
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
}



void LoginWindow::onLoginClicked() {
    // Here you'd usually verify username and password
    emit loginSuccessful(usernameEdit->text());
    this->close(); // Close the login window
}

QString LoginWindow::getUsername() {
    return usernameEdit->text();
}
