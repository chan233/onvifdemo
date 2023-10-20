QT       += core gui network testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    OnvifDevice.cpp \
    main.cpp \
    mainwindow.cpp \
    #player.cpp \
    #viedoframe.cpp
    testclass.cpp

HEADERS += \
    OnvifDevice.h \
    mainwindow.h \
    #player.h \
    #viedoframe.h
    #onvifheads.h
    testclass.h

FORMS += \
    mainwindow.ui\
    #viedoframe.ui

TRANSLATIONS += \
    onvifdemo_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target






win32{
    #INCLUDEPATH += $$PWD/src/include
    INCLUDEPATH += C:/Users/HUAWEI/Desktop/env/libONVIF/build/install/include/
    #INCLUDEPATH += /opt/ffmpeg/include
    CONFIG(release, debug|release){
            LIBS += -L$$PWD/src/winlib/Release/ -lonvifanalytics -lonvifcommon  -lonvifdiscovery\
            -lonvifdisplay -lonvifevent -lonvifimaging -lonvifmedia2 -lonvifmedia -lonvifptz \
            -lonvifreceiver -lonvifrecording -lonvifreplay -lonvifdevice #-lonvifManager
    }
    CONFIG(debug, debug|release){


        LIBS += -LC:/Users/HUAWEI/Desktop/env/libONVIF/build/install/lib/ -lonvifanalyticsd -lonvifcommond  -lonvifdiscoveryd\
-lonvifdisplayd -lonvifeventd -lonvifimagingd -lonvifmedia2d -lonvifmediad -lonvifptzd \
-lonvifreceiverd -lonvifrecordingd -lonvifreplayd -lonvifdeviced #-lonvifManagerd

#        LIBS += -L$$PWD/src/winlib/Debug/ -lonvifanalyticsd -lonvifcommond -lonvifdeviced -lonvifdiscoveryd\
#        -lonvifdisplayd -lonvifeventd -lonvifimagingd -lonvifmedia2d -lonvifmediad -lonvifptzd -lonvifManagerd\
#        -lonvifreceiverd -lonvifrecordingd -lonvifreplayd

#        LIBS += -L"/opt/ffmpeg/lib/"
#        LIBS += -lavutil \
#                -lavcodec \
#               -lavdevice \
#                -lavfilter \
#                -lavformat \
#                -lavutil \
#                -lswresample \
#                -lswscale
    }
}
else{
        INCLUDEPATH += /home/glhr/Desktop/libONVIF/build/install/debug/include

        LIBS += -L/home/glhr/Desktop/libONVIF/build/install/debug/lib -lonvifanalyticsd -lonvifcommond  -lonvifdiscoveryd\
            -lonvifdisplayd -lonvifeventd -lonvifimagingd -lonvifmedia2d -lonvifmediad -lonvifptzd \
            -lonvifreceiverd -lonvifrecordingd -lonvifreplayd -lonvifdeviced #-lonvifManagerd

        QMAKE_LFLAGS += -Wl,-rpath=./

}

