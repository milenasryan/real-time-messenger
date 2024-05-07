QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    chatserver.cpp \
    encryptor.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    chatserver.h \
    encryptor.h \
    loginwindow.h \
    mainwindow.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
