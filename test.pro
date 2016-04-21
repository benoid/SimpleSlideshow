QT       += core gui
CONFIG += console c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = run_tests
TEMPLATE = app


SOURCES += $$PWD/test/test_main.cpp \
    $$PWD/test/test_class_main.cpp \
    $$PWD/test/slide_tests.cpp \
    $$PWD/test/slide_queue_tests.cpp \
    $$PWD/test/slide_directory_tests.cpp \
    $$PWD/src/lib/slideshow_display.cpp \
    $$PWD/src/lib/slide.cpp \
    $$PWD/src/lib/slide_queue.cpp \
    $$PWD/src/lib/slide_directory.cpp \



HEADERS  += $$PWD/test/test_suite_macros.h \
    $$PWD/test/test_class_main.h \
    $$PWD/test/slide_tests.h \
    $$PWD/test/slide_queue_tests.h \
    $$PWD/test/slide_directory_tests.h \
    $$PWD/src/lib/slideshow_display.h \
    $$PWD/src/lib/slide.h \
    $$PWD/src/lib/ansi_colors.h \
    $$PWD/src/lib/slide_queue.h \
    $$PWD/src/lib/slide_directory.h \


