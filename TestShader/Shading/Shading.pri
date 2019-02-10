!SHADING_PRI {

CONFIG += SHADING_PRI

INCLUDEPATH += $$PWD/../

HEADERS += \
    $$PWD/crossshading.h\
    $$PWD/planevector.h\
    $$PWD/planevectordrawer.h\
    $$PWD/point.h\
    $$PWD/trianglespeller.h

SOURCES += \
    $$PWD/crossshading.cpp\
    $$PWD/planevector.cpp\
    $$PWD/planevectordrawer.cpp\
    $$PWD/point.cpp\
    $$PWD/trianglespeller.cpp
}
