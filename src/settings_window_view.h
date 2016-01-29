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

/* settings_window_view.h

   Author: David Benoit
   Purpose: Creates a gui window for user to adjust
            settings. Is respomsible for displaying info
            to the screen, and also for manipulating the
            filesystem to hide floders from the slideshow
            upon user request. */

#ifndef SETTINGSWINDOWVIEW_H
#define SETTINGSWINDOWVIEW_H

#include <QDialog>
#include <QString>
#include <QTableWidget>
#include <QList>
#include "queue_sort_order.h"
#include "slide_directory.h"

namespace Ui {
  class SettingsWindowView;
}

class SettingsWindowView : public QDialog
{
  Q_OBJECT
public:
  explicit SettingsWindowView(QWidget *parent = 0);
  ~SettingsWindowView();

  // Sets the values in the gui text field to the
  // Corresponding values of the classes private variables
  void set_up_gui();

  // Sets the tab widget's focus to the main tab
  void set_focus_main_tab();

  // Sets the tab widget's focus to the folders view tab
  void set_focus_folders_tab();

  // Mutators
  void set_slide_folder_path(QString set_path);
  void set_main_timer_interval(int set_interval);
  void set_marketing_timer_interval(int set_interval);
  void set_fullscreen_disabled(bool set_disabled);
  void set_begin_on_marketing_slide(bool set_enabled);
  void set_randomize_images(bool set_enabled);
  void set_slide_directory_list(QList<SlideDirectory> dir_list);
  void set_marketing_order(QueueSortOrder option);
  void set_main_order(QueueSortOrder option);
  void set_marketing_option(MarketingPlaybackOption option);


  // Accessors
  QueueSortOrder main_order_option();
  QueueSortOrder marketing_order_option();
  MarketingPlaybackOption marketing_option();
  bool begin_on_marketing_slide_bool();
  bool randomize_images_bool();
  int main_timer_interval();
  int marketing_timer_interval();
  bool fullscreen_disabled();
  QString slide_folder_path();

signals:
  void ok_button_pressed();
  void cancel_button_pressed();
  void apply_button_pressed();
  void slide_folder_changed();

private:
  Ui::SettingsWindowView *ui;

  // Display stuff

  QString slide_folder_path_;
  QList<SlideDirectory> slide_directory_list_;

  QTableWidgetItem * table_item;
  bool fullscreen_disabled_bool_;
  bool begin_on_marketing_slide_bool_;
  bool randomize_images_bool_;
  int main_timer_interval_;
  int marketing_timer_interval_;

  QueueSortOrder main_sort_order_;
  QueueSortOrder marketing_sort_order_;
  MarketingPlaybackOption marketing_playback_option_;


  // Private methods
  void apply_settings();

private slots:
  void on_buttonBox_accepted();
  void on_buttonBox_rejected();
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
};

#endif // SETTINGSWINDOWVIEW_H
