CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(vListWidgetPlugin)
TEMPLATE    = lib

RESOURCES   = \
    vListWidgetResources.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(vListWidget.pri)

HEADERS += \
    vListWidgetPlugin.h

SOURCES += \
    vListWidgetPlugin.cpp
