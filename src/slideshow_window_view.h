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
    along with SimpleSlideshow.  If not, see <http://www.gnu.org/licenses/>.
    slideshow_window_view.h */


 /* Author: David Benoit
    Purpose: Creates a window to display image
             and video slides. */

#ifndef SLIDESHOW_WINDOW_VIEW_H
#define SLIDESHOW_WINDOW_VIEW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>
#include <QMenu>
#include <QString>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QStackedWidget>
#include "slideshow_data_model.h"


class SlideshowWindowView : public QMainWindow
{
  Q_OBJECT

public:
  SlideshowWindowView(QWidget *parent = 0);
  ~SlideshowWindowView();

public slots:

  // Takes the path to an image file and
  // displays it on the screen
  int display_image(QString image);

  // Takes the path to a video file and
  // plays it on the screen
  void display_video(QString video);

  // Sets stacked_widget_'s focus to image player
  void hide_video_player();

  // Displays the right-click context menu to the screen
  void show_context_menu(const QPoint &pos);

  // Emits settings settings_option_clicked signal
  // SlideshowController will open the settings window
  void show_settings_view();

  // Opens the About Slideshow window
  void show_about_slideshow();

  // Opens the About Qt window
  void show_about_qt();

  // Closes the application
  void quit_application();

  // Display no images error to the screen
  void display_no_images_error();


signals:
  void about_slideshow_clicked();
  void about_qt_clicked();
  void settings_option_clicked();
  void video_finished_playing();

private:

/*** Qt Window and Display related items ***/
  QStackedWidget * stacked_widget_;
  QScrollArea* scroll_area_widget_;
  QLabel * image_display_label_;
  QMediaPlayer * media_player_;
  QVideoWidget * video_widget_;
  QMediaPlaylist * media_playlist_;



/*** Context menu and corresonding actions ***/
  // Right-click context menu
  QMenu * context_menu_;

  // Opens settings window to main tab
  QAction * show_settings_view_action_;

  // Opens the About Slideshow window
  QAction * show_about_slideshow_action_;

  // Opens the About Qt window
  QAction * show_about_qt_action_;

  // Quits the application
  QAction * quit_application_action_;

  bool video_player_exists_;

};

#endif // SLIDESHOW_WINDOW_VIEW_H
