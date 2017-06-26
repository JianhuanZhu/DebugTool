#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T08:44:16
#
#-------------------------------------------------

QT       += core gui sql

TARGET = DebugTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageview.cpp \
    vialview.cpp \
    CmdCan.cpp \
    CanObject.cpp \
    ErrorInfo.cpp \
    dbmanager.cpp \
    armview.cpp \
    injectorview.cpp

HEADERS  += mainwindow.h \
    imageview.h \
    vialview.h \
    CmdCan.h \
    can/raw.h \
    can/ioctl.h \
    can/error.h \
    can/dev.h \
    can/core.h \
    can/bcm.h \
    CanObject.h \
    ErrorInfo.h \
    dbmanager.h \
    armview.h \
    injectorview.h

FORMS    += mainwindow.ui \
    imageview.ui \
    vialview.ui \
    armview.ui \
    injectorview.ui


INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += -L /usr/local/lib

LIBS += -lopencv_highgui -lopencv_core -lopencv_calib3d \
        -lopencv_features2d -lopencv_flann -lopencv_imgcodecs \
        -lopencv_imgproc -lopencv_videoio

OTHER_FILES += \
    can/Kbuild \
    images/sorry.png

RESOURCES += \
    image.qrc
