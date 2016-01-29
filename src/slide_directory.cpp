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

/* slide_directory.cpp

   Author: David Benoit
   Purpose: Implementation of the SlideDirectory class. */

#include "slide_directory.h"

SlideDirectory::SlideDirectory()
{
  marketing_folder_ = false;
  exclude_from_slideshow_ = false;
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





















