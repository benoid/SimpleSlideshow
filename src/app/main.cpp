#include "slideshow_display.h"
#include "test_class_main.h"
#include <QApplication>

#define TESTING_STUFF
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  //SlideshowDisplay s;
  //s.show();

  TestClassMain t;
  t.run();
  return  a.exec();
}
