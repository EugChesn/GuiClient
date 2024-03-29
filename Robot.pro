#-------------------------------------------------
#
# Project created by QtCreator 2019-07-15T17:31:50
#
#-------------------------------------------------

QT       += core gui opengl
QT += network
QT += gamepad


LIBS += -L$$PWD/source/mrvisual/ -lMRVisualLib

INCLUDEPATH += $$PWD/source/mrvisual
DEPENDPATH += $$PWD/source/mrvisual

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Robot
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
        dialog.cpp \
        main.cpp \
        mainwindow.cpp \
        settingconst.cpp \
        settings.cpp \
        tcpcontrol.cpp \
        testguithread.cpp \
        videomanagegcreator.cpp \
        videomanager.cpp

HEADERS += \
        dialog.h \
        mainwindow.h \
        settingconst.h \
        settings.h \
        tcpcontrol.h \
        testguithread.h \
        videomanagegcreator.h \
        videomanager.h

FORMS += \
        dialog.ui \
        mainwindow.ui \
        settings.ui


#INCLUDEPATH += C:\opencv\opencv\opencv-bin\install\include
#LIBS +=-L"C:\opencv\opencv\opencv-bin\install\x86\mingw\lib"
#LIBS +=  \
#-lopencv_core410 \
#-lopencv_highgui410 \
#-lopencv_imgproc410 \
#-lopencv_photo410 \
#-lopencv_imgcodecs410 \
#-lopencv_video410 \
#-lopencv_videoio410 \
INCLUDEPATH += C:/OpenCv/opencv/opencv_bin/install/include/
LIBS +=-L"C:/OpenCv/opencv/opencv_bin/install/x86/mingw/lib/"
LIBS +=  \
-lopencv_core410 \
-lopencv_highgui410 \
-lopencv_imgproc410 \
-lopencv_photo410 \
-lopencv_imgcodecs410 \
-lopencv_video410 \
-lopencv_videoio410



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resurse.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/MRVisualLib/release/ -lMRVisualLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/MRVisualLib/debug/ -lMRVisualLib

INCLUDEPATH += $$PWD/MRVisualLib/debug
DEPENDPATH += $$PWD/MRVisualLib/debug
