/* slide_directory.cpp
 *
 * Author: David Benoit
 * Purpose: Implementation of the SlideDirectory class
 */

#include "slide_directory.h"

SlideDirectory::SlideDirectory()
{
  marketing_folder_ = false;
}

QString SlideDirectory::name()
{
  return name_;
}

QString SlideDirectory::full_path()
{
  return full_path_;
}

QStringList SlideDirectory::file_list()
{
  return file_list_;
}

bool SlideDirectory::is_marketing_folder()
{
  return marketing_folder_;
}

bool SlideDirectory::is_excluded()
{
  return exclude_from_slideshow_;
}

void SlideDirectory::set_dir_name(QString set_name)
{
  name_ = set_name;
}

void SlideDirectory::set_full_path(QString set_path)
{
  full_path_ = set_path;
}

void SlideDirectory::append_file_list(QString file)
{
  file_list_.append(file);
}

void SlideDirectory::set_marketing_folder(bool set_marketing_bool)
{
  marketing_folder_ = set_marketing_bool;
}

void SlideDirectory::set_exclude_from_show(bool set_exclude_bool)
{
  exclude_from_slideshow_ = set_exclude_bool;
}





















