QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    OnvifDevice.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    viedoframe.cpp

HEADERS += \
    OnvifDevice.h \
    mainwindow.h \
    player.h \
    viedoframe.h
    #onvifheads.h

FORMS += \
    mainwindow.ui\
    viedoframe.ui

TRANSLATIONS += \
    onvifdemo_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# linux


CONFIG(debug, debug|release){
INCLUDEPATH+=$$PWD/src/include/
#LIBS +=-L$$PWD/src/lib -lonvifXd -lonvifdeviced

#LIBS +=-L/home/chan/Desktop/git/libONVIF/build/install/debug/lib -lonvifXd -lonvifdeviced
#INCLUDEPATH+=/home/chan/Desktop/git/libONVIF/build/install/debug/include
LIBS +=-L/home/chan/Desktop/git/libONVIF/build/install/debug/lib -lonvifXd
}
CONFIG(release, debug|release){

LIBS +=-L$$PWD/src/lib -lonvifX -lonvifdevice
}
QMAKE_LFLAGS += -Wl,-rpath=./

INCLUDEPATH += /opt/ffmpeg/include

# ffmpeg

LIBS += -L"/opt/ffmpeg/lib/"
LIBS += -lavutil \
        -lavcodec \
       -lavdevice \
        -lavfilter \
        -lavformat \
        -lavutil \
        -lswresample \
        -lswscale

