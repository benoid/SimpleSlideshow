#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T09:03:17
#
#-------------------------------------------------

QT       += core gui multimediawidgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleSlideshow
TEMPLATE = app


SOURCES += main.cpp\
        slideshow_window_view.cpp \
    settings_window_view.cpp \
    slideshow_controller.cpp \
    slideshow_queue.cpp \
    slideshow_data_model.cpp \
    slide_directory.cpp \
    slide.cpp \
    about_window_view.cpp

HEADERS  += slideshow_window_view.h \
    settings_window_view.h \
    slideshow_controller.h \
    slideshow_queue.h \
    slideshow_data_model.h \
    slide_directory.h \
    slide.h \
    queue_sort_order.h \
    about_window_view.h

FORMS += settings_window_view.ui \
    about_window_view.ui

DISTFILES += \
    dependencies_list.txt
