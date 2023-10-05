QT += widgets

TEMPLATE = lib
DEFINES += QTPLOT_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    qtplot.cpp

HEADERS += \
    QtPlot_global.h \
    qtplot.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    qtplot.ui

### qwt
QWT_DIR = D:/Library/qwt/qwt-6.2.0
INCLUDEPATH += $$QWT_DIR/include
LIBS += $$QWT_DIR/lib/Release/qwt.lib
