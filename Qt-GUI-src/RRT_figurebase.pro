#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T17:38:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RRT_figurebase
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qimagelabel.cpp

HEADERS  += mainwindow.h \
    qimagelabel.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\\OpenCV-3.1.0\\build\\install\\include

LIBS += -LC:\\OpenCV-3.1.0\\build\\lib\\Debug \
    -lopencv_aruco310d \
    -lopencv_core310d \
    -lopencv_imgcodecs310d \
    -lopencv_imgproc310d \
    -lopencv_ml310d \
    -lopencv_objdetect310d \
    -lopencv_photo310d \
    -lopencv_shape310d \
    -lopencv_stitching310d \
    -lopencv_superres310d \
    -lopencv_ts310d \
    -lopencv_video310d \
    -lopencv_videoio310d \
    -lopencv_videostab310d \
    -lopencv_calib3d310d \
    -lopencv_features2d310d \
    -lopencv_flann310d \
    -lopencv_highgui310d
