#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T14:11:40
#
#-------------------------------------------------

QT       += core gui
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleSlideshow2
TEMPLATE = app


SOURCES += main.cpp\
        slideshow_display.cpp \
    slide.cpp \
    slide_tests.cpp \
    slide_queue.cpp \
    slide_directory_tests.cpp \
    slide_directory.cpp \
    slide_queue_tests.cpp \
    test_class_main.cpp


HEADERS  += slideshow_display.h \
    slide.h \
    ansi_colors.h \
    slide_tests.h \
    test_suite_macros.h \
    slide_queue.h \
    slide_directory_tests.h \
    slide_directory.h \
    slide_queue_tests.h \
    test_class_main.h

