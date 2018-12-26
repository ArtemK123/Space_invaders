#-------------------------------------------------
#
# Project created by QtCreator 2018-11-29T13:44:30
#
#-------------------------------------------------

QT += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Space_invaders
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    classes.cpp \
    texture.cpp \
    units.cpp \
    bullets.cpp \
    window.cpp \
    game.cpp \
    sound.cpp \
    record_file.cpp

HEADERS += \
    classes.h \
    texture.h \
    units.h \
    bullets.h \
    window.h \
    game.h \
    interfaces.h \
    sound.h \
    record_file.h

FORMS += \
    menu.ui \
    records.ui \
    new_record.ui \
    window.ui \
    game.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source_files.qrc

DISTFILES += \
    sources/sprite_sheet.png \
    sources/high_scores.txt \
    sources/sounds/spaceinvaders2.ram \
    sources/sounds/explosion.wav \
    sources/sounds/fastinvader1.wav \
    sources/sounds/fastinvader2.wav \
    sources/sounds/fastinvader3.wav \
    sources/sounds/fastinvader4.wav \
    sources/sounds/invaderkilled.wav \
    sources/sounds/shoot.wav \
    sources/sounds/ufo_highpitch.wav \
    sources/sounds/ufo_lowpitch.wav \
    sources/sounds/spaceinvaders1.mpeg
