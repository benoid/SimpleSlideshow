#include "slideshow_display.h"
#include "test_class_main.h"
#include <QDebug>

SlideshowDisplay::SlideshowDisplay(QWidget *parent)
    : QMainWindow(parent)
{
  TestClassMain t;
  t.run();
  qWarning () << "hello";
}

SlideshowDisplay::~SlideshowDisplay()
{

}
