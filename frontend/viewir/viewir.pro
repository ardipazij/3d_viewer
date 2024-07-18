QT       += core gui openglwidgets
QT += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(qgifimage/src/gifimage/qtgifimage.pri)
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../backend/affine_convert.c \
    ../../backend/base_function.c \
    ../../backend/matrix/s21_matrix.c \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../backend/s21_3dviewer_v1.0.h \
    ../../backend/matrix/s21_matrix.h \
    glwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
