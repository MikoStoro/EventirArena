QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Hexmath.cpp \
    banner.cpp \
    board.cpp \
    coords.cpp \
    eye.cpp \
    field.cpp \
    fieldcontainer.cpp \
    gamescreenui.cpp \
    graphichexagon.cpp \
    item.cpp \
    main.cpp \
    pattern.cpp \
    player.cpp \
    shield.cpp \
    spawnaction.cpp \
    spear.cpp \
    sword.cpp \
    window.cpp

HEADERS += \
    banner.h \
    board.h \
    coords.h \
    directions.h \
    enums.h \
    eye.h \
    field.h \
    fieldcontainer.h \
    gamescreenui.h \
    graphichexagon.h \
    item.h \
    pattern.h \
    player.h \
    shield.h \
    spawnaction.h \
    spear.h \
    sword.h \
    window.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
