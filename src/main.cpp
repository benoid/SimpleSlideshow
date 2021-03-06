/*  Copyright (C) 2016 David Benoit

    This file is part of SimpleSlideshow.

    SimpleSlideshow is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SimpleSlideshow is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SimpleSlideshow.  If not, see <http://www.gnu.org/licenses/>. */

/* main.cpp

   Purpose: main function for SimpleSlideshow. */


#include <QApplication>
#include "slideshow_controller.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SlideshowController c;
  c.begin_slideshow();

  return a.exec();
}
