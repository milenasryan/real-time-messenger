#include "mainwindow.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LoginWindow login;
    MainWindow w;

    QObject::connect(&login, &LoginWindow::loginSuccessful, [&](const QString &username){
        w.setUsername(username); // Implement setUsername in MainWindow
        w.show();
    });

    login.show();
    return a.exec();
}
