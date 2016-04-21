
#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T14:11:40
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleSlideshow
TEMPLATE = app
CONFIG += gui console


SOURCES += \
    $$PWD/src/lib/slideshow_display.cpp \
    $$PWD/src/lib/slide.cpp \
    $$PWD/src/lib/slide_queue.cpp \
    $$PWD/src/lib/slide_directory.cpp \



HEADERS  += $$PWD/src/lib/slideshow_display.h \
    $$PWD/src/lib/slide.h \
    $$PWD/src/lib/ansi_colors.h \
    $$PWD/src/lib/slide_queue.h \
    $$PWD/src/lib/slide_directory.h \

