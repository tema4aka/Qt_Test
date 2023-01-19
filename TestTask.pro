QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    databasemanager.cpp \
    inventory.cpp \
    inventorydelegate.cpp \
    inventorymodel.cpp \
    inventoryview.cpp \
    itemlabel.cpp \
    itemmimedata.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp

HEADERS += \
    databasemanager.h \
    inventory.h \
    inventorydelegate.h \
    inventorymodel.h \
    inventoryview.h \
    itemlabel.h \
    itemmimedata.h \
    mainwindow.h \
    menu.h




qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
