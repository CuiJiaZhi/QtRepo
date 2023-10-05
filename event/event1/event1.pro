QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

### 设置源代码的字符集编码为UTF-8，项目中的源文件将被编译器视为使用UTF-8编码
QMAKE_CXXFLAGS += /source-charset:utf-8
### 设置执行结果的字符集编码为UTF-8。这意味着在运行应用程序时，执行结果将被视为使用UTF-8编码
QMAKE_CXXFLAGS += /execution-charset:utf-8

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
