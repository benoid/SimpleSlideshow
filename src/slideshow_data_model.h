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

/* slideshow_data_model.h

   Author: David Benoit
   Purpose: Container class which stores all
            configureable settings.  Is responsible for
            creating and managing a SlideshowQueue
            object. */

#ifndef SLIDESHOWDATAMODEL_H
#define SLIDESHOWDATAMODEL_H

#include <QObject>
#include <QString>
#include "slide_directory.h"
#include "slideshow_queue.h"
#include "queue_sort_order.h"

class SlideshowDataModel : public QObject
{
  Q_OBJECT
public:
  explicit SlideshowDataModel(QObject *parent = 0);
  ~SlideshowDataModel();

/*** Mutators ***/
  void set_profile_folder(QString folder);
  void set_image_folder(QString folder);
  void set_main_timer_interval(int millisecs);
  void set_marketing_timer_interval(int millisecs);
  void set_fullscreen_disabled(bool set);
  void set_config_file(QString file);
  void set_video_disabled(bool set);
  void set_begin_on_marketing(bool set);
  void set_init_delay(int num_millisecs);
  void set_indiv_info_slide_interval(int set);
/*** Accessors ***/
  SlideshowQueue * slideshow_queue();
  QString profile_folder_path();
  QString main_image_folder_path();
  QString config_file_path();
  QList<SlideDirectory> * slide_dir_list();
  int main_timer_interval();
  int marketing_timer_interval();
  bool fullscreen_disabled();
  bool video_disabled();
  bool begin_on_marketing();
  int init_delay_millisecs();
  int indiv_info_slide_interval();

signals:

public slots:

private:
  // Stores all of the slide objects
  SlideshowQueue * slideshow_queue_;

  // Stores a list of first-level
  // subrirectories in the main image
  // folder
  QList<SlideDirectory> slide_dir_list_;

  // Stores the filesystem path to the
  // profile folder
  QString profile_folder_path_;

  // Stores the filesystem path to the
  // top level image folder
  QString main_image_folder_path_;

  // Stores the path to the config file
  QString config_file_path_;

  // Timer countdown intervals
  int main_timer_interval_;
  int marketing_timer_interval_;
  int indiv_info_slide_interval_;

  // True if fullscreen display is disabled
  bool fullscreen_disabled_bool_;

  // True if video playback is disabled
  bool video_disabled_;

  // True means a marketing slide will be queued
  // on application startup
  bool begin_on_marketing_;

  // Delay display of first slide to account for external
  // desktop effects
  int init_delay_ms_;

};

#endif // SLIDESHOWDATAMODEL_H
