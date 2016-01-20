/* slide.cpp
 *
 * Author: David Benoit
 * Purpose: Implementation of the Slide class
 */

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

