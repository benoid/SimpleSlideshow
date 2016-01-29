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

/* slide.h

   Author: David Benoit
   Purpose: Container class representing
            a slideshow slide.  Stores
            file path and slide type
            (IMAGE, VIDEO, or NULL_SLIDE) */

#ifndef SLIDE_H
#define SLIDE_H

#include <QString>
#include <QDebug>

enum SlideType
{
  NULL_SLIDE,IMAGE, VIDEO, INVALID_SLIDE
};

class Slide
{
public:
  Slide();
  Slide(QString path, SlideType type);
  Slide(QString path);

/*** Mutators ***/
  void set_full_path(QString path);
  void set_slide_type(SlideType type);


/*** Accessors ***/
  QString full_path();
  SlideType slide_type();

private:
  QString full_path_;
  SlideType slide_type_;

  SlideType get_slide_type(QString path);
};

#endif // SLIDE_H
