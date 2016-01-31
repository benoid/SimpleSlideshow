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

/* slideshow_controller.h

   Author: David Benoit
   Purpose: Driver class for the slideshow
            creates and manages a SlideshowDataModel
            object, SlideshowWindowView object,
            and SettingsWindowView object. Sends data from
            config file to SlideshowDataModel.  Is responsible for
            starting the slideshow. */

#ifndef SLIDESHOWCONTROLLER_H
#define SLIDESHOWCONTROLLER_H

#include <QObject>
#include <QTimer>
#include "queue_sort_order.h"
#include "slideshow_window_view.h"
#include "slideshow_data_model.h"
#include "settings_window_view.h"
#include "about_window_view.h"

class SlideshowController : public QObject
{
  Q_OBJECT
public:
  explicit SlideshowController(QObject *parent = 0);
  ~SlideshowController();
  
  // Starts the slideshow
  void begin_slideshow();

signals:

public slots:
/*** Slideshow SLOTs ***/

  // Display the next slide in the slide queue
  void show_next_slide();

  // Tell the slideshow_queue object that
  // The next image should be a marketing slide
  void queue_marketing_slide();

/*** Context menu SLOTs ***/
  // Show context menu
/*** Settings GUI SLOTs ***/

  // Display the settings gui to the screen
  void show_settings_view();

  // Shows the about slideshow window
  void show_about_slideshow();

  // Shows the about Qt window
  void show_about_qt();

  // Import settings from gui, save them to
  // to the config file, and close the gui
  void gui_ok_button_pressed();

  // Close the gui without saving changes
  void gui_cancel_button_pressed();

  // Import settings from gui, save them to
  // to the config file, and close the gui
  void gui_apply_button_pressed();

  // Restart timers and continue slideshow
  void post_video_unpause();

private:
  SlideshowDataModel * slideshow_data_model_;
  SlideshowWindowView *slideshow_window_view_;
  SettingsWindowView * settings_window_view_;
  AboutWindowView *about_window_view_;



/*** Slideshow Timers ***/
  // Slide is updated upon timeout
  QTimer main_slide_timer_;

  // Marketing slides play upon timeout
  QTimer marketing_slide_timer_;

/*** Private function members ***/
  void set_all_settings_to_default();
  void ensure_folder_structure();
  void save_config_file(QString file_path);
  void parse_config_file(QString file_path);

  void export_settings_to_gui();
  void import_settings_from_gui();

  // notifies user of an error with the config fils
  void warn_config_error(QString key, QString value_str);

  // Checks main slide folder,
  // adds new slides,
  // removes nonexistant slides
  void refresh_directory_list();
  void build_slide_queue();

};

#endif // SLIDESHOWCONTROLLER_H
