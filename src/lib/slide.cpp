#include <QFileInfo>

#include "slide.h"

Slide::Slide()
{
  file_path_ = "";
}

Slide::Slide(QString file_path)
{
  file_path_ = file_path;
}

QString Slide::file_path()
{
  return file_path_;
}

QString Slide::absolute_file_path()
{
  return (QFileInfo(this->file_path()).absoluteFilePath());
}

SlideType Slide::slide_type()
{
  if (file_path_ == "")
    return INVALID_SLIDE;

  QString extension = QFileInfo(file_path_).completeSuffix().toLower();
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

bool Slide::is_valid()
{
  return ((bool) this->slide_type() && this->exists());
}

bool Slide::exists()
{
  return QFileInfo(file_path_).exists();
}

void Slide::set_file_path(QString file_path)
{
  file_path_ = file_path;
}
