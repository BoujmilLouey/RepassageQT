QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    dbconnection.cpp \
    main.cpp \
    mainwindow.cpp \
    dbconnection.cpp \
    client.cpp \
    commande.cpp

HEADERS += \
    dbconnection.h \
    mainwindow.h \
    dbconnection.h \
    client.h \
    commande.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
