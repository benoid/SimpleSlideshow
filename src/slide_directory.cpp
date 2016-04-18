#include "slide_directory.h"

SlideDirectory::SlideDirectory(QString dir_path)
{
  dir_path_ = dir_path;
}

bool SlideDirectory::is_informational()
{
  return dir_path_.contains("-info");
}

QList<Slide> SlideDirectory::refresh_contents()
{
  QList<Slide> new_contents;

  if (!QDir(dir_path_).exists())
    {
      qDebug() << DEBUG_CONSOLE_WARNING_COLOR <<
                  "Warning: " << DEBUG_CONSOLE_DEFAULT_COLOR <<
                  "Directory "<< dir_path_ <<
                  " does not exist.";
      return new_contents;
    }
  QDirIterator itr(dir_path_,
                   QDir::Files | QDir::NoSymLinks |
                   QDir::Hidden, QDirIterator::Subdirectories);
  int entry_count = 0;
  while (itr.hasNext())
    {
      itr.next();

      Slide new_slide(itr.filePath());
      if (new_slide.is_valid())
        {
          if (!slide_set_.contains(new_slide))
            {
              this->insert(new_slide);
              new_contents << new_slide;
            }

        }
      ++entry_count;
    }
  if (this->size() > entry_count)
    purge_nonexistant_entries();

  return new_contents;
}

QList<Slide> SlideDirectory::qList()
{
  SlideDirectoryIterator itr;
  QList<Slide> l;
  if (this->size() == 0)
    return l;

  for (itr = this->begin(); itr != this->end(); ++itr)
    {
      Slide s = *itr;
      l.append(s);
    }
  return l;
}

void SlideDirectory::build_from_local_dir()
{
  if (!QDir(dir_path_).exists())
    {
      qDebug() << DEBUG_CONSOLE_WARNING_COLOR <<
                  "Warning: " << DEBUG_CONSOLE_DEFAULT_COLOR <<
                  "Directory "<< QDir(dir_path_).absolutePath() <<
                  " does not exist.";
      return;
    }
  slide_set_.clear();
  QDirIterator itr(dir_path_,
                   QDir::Files | QDir::NoSymLinks |
                   QDir::Hidden, QDirIterator::Subdirectories);
  while (itr.hasNext())
    {
      itr.next();
      Slide new_slide(itr.filePath());
      if (new_slide.is_valid())
        {
          this->insert(new_slide);
        }
    }
}

bool SlideDirectory::contains(Slide s)
{
  Slide t(s.absolute_file_path());
  return slide_set_.contains(t);
}

SlideDirectoryIterator SlideDirectory::begin()
{
  return slide_set_.begin();
}

SlideDirectoryIterator SlideDirectory::end()
{
  return slide_set_.end();
}

void SlideDirectory::insert(Slide s)
{
  Slide t(QFileInfo(s.file_path()).absoluteFilePath());
  slide_set_.insert(t);
}

void SlideDirectory::remove(Slide s)
{
  slide_set_.remove(s);
}

void SlideDirectory::purge_nonexistant_entries()
{
  if (this->size() == 0)
    return;

  if (!QDir(dir_path_).exists())
    return;
  SlideDirectory temp(dir_path_);
  temp.build_from_local_dir();
  QList<Slide> delete_list;
  SlideDirectoryIterator itr;
  for (itr = this->begin(); itr != this->end(); ++itr)
    {
      Slide s = *itr;
      if (!temp.contains(s))
        delete_list << s;
    }
  foreach (Slide s, delete_list)
    {
      this->remove(s);
    }
}

QString SlideDirectory::dir_path()
{
  return QDir(dir_path_).absolutePath();
}

int SlideDirectory::size()
{
  return slide_set_.size();
}




