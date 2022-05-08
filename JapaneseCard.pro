QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 exceptions

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    $$PWD/ui/src/aboutdialog.cpp \
    $$PWD/ui/src/cardedit.cpp \
    $$PWD/tools/src/databyte.cpp \
    $$PWD/tools/src/dbtool.cpp \
    $$PWD/tools/src/exception.cpp \
    $$PWD/main.cpp \
    $$PWD/ui/src/japanesecard.cpp

HEADERS += \
    $$PWD/ui/include/aboutdialog.h \
    $$PWD/ui/include/cardedit.h \
    $$PWD/tools/include/cardstruct.h \
    $$PWD/tools/include/databyte.h \
    $$PWD/tools/include/dbtool.h \
    $$PWD/tools/include/exception.h \
    $$PWD/ui/include/japanesecard.h \
    $$PWD/tools/include/readonlydelegate.h

FORMS += \
    $$PWD/ui/aboutdialog.ui \
    $$PWD/ui/cardedit.ui \
    $$PWD/ui/japanesecard.ui

win32 {
    QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    $$PWD/Resource/qsrc.qrc
