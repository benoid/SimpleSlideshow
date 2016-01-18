#include <QApplication>
#include "slideshow_controller.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SlideshowController c;
  c.begin_slideshow();

  return a.exec();
}
