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

/* slide.cpp

   Author: David Benoit
   Purpose: Implementation of the Slide class. */

#include <QFileInfo>
#include "slide.h"

Slide::Slide()
{

}

Slide::Slide(QString path, SlideType type)
{
  full_path_ = path;
  slide_type_ = type;
}

Slide::Slide(QString path)
{
  full_path_ = path;
  slide_type_ = get_slide_type(path);

}

void Slide::set_full_path(QString path)
{
  full_path_ = path;
}

void Slide::set_slide_type(SlideType type){
  slide_type_ = type;
}

QString Slide::full_path()
{
  return full_path_;
}

SlideType Slide::slide_type()
{
  return slide_type_;
}

SlideType Slide::get_slide_type(QString path)
{
  QString extension = QFileInfo(path).completeSuffix().toLower();
  if (extension.contains("jpg"))
    {
      return IMAGE;
    }
  else if (extension.contains("jpeg"))
    {
      return IMAGE;
    }
  else if (extension.contains("gif"))
    {
      return IMAGE;
    }
  else if (extension.contains("bmp"))
    {
      return IMAGE;
    }
  else if (extension.contains("png"))
    {
      return IMAGE;
    }
  else if (extension.contains("pbm"))
    {
      return IMAGE;
    }
  else if (extension.contains("pgm"))
    {
      return IMAGE;
    }
  else if (extension.contains("ppm"))
    {
      return IMAGE;
    }
  else if (extension.contains("xbm"))
    {
      return IMAGE;
    }
  else if (extension.contains("xpm"))
    {
      return IMAGE;
    }
  else if (extension.contains("ogv"))
    {
      return VIDEO;
    }
  else if (extension.contains("avi"))
    {
      return VIDEO;
    }
  else if (extension.contains("mov"))
    {
      return VIDEO;
    }
  else if (extension.contains("mpg"))
    {
      return VIDEO;
    }
  else if (extension.contains("mp4"))
    {
      return VIDEO;
    }
  else if (extension.contains("flv"))
    {
      return VIDEO;
    }
  else if (extension.contains("wmv"))
    {
      return VIDEO;
    }
  else if (extension.contains("ogg"))
    {
      return VIDEO;
    }
  else
  {
      return INVALID_SLIDE;
  }
}

