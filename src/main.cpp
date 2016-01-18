#include <QApplication>
#include "slideshow_controller.h"
/*
 * Dependencies:
 *   - mesa-libgl
 *   - gstreamer-plugins-good
 *
 *
 */

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SlideshowController c;
  c.begin_slideshow();

  return a.exec();
}
