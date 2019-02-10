!SHADINGTESTS_PRI {

CONFIG += SHADINGTESTS_PRI

INCLUDEPATH += $$PWD/../

include (Shading.pri);

HEADERS += \
    $$PWD/planevectortests.h

SOURCES += \
    $$PWD/planevectortests.cpp
}
