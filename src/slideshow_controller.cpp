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

/* slideshow_controller.cpp
 *
   Author: David Benoit
   Purpose: Implementation of the SlideshowController class. */

#include <QDesktopServices>
#include <QDesktopWidget>
#include <QTextStream>
#include <QDir>
#include <QDirIterator>
#include "slideshow_controller.h"

SlideshowController::SlideshowController(QObject *parent) : QObject(parent)
{
/*************************/
  slideshow_window_view_ = new SlideshowWindowView;
  slideshow_window_view_->resize(800, 450);
  slideshow_data_model_ = new SlideshowDataModel;
  settings_window_view_ = new SettingsWindowView;
  about_window_view_ = new AboutWindowView;

  connect(slideshow_window_view_, SIGNAL(settings_option_clicked()),
        this, SLOT(show_settings_view()));
  connect(slideshow_window_view_, SIGNAL(video_finished_playing()),
          this, SLOT(post_video_unpause()));
  connect(slideshow_data_model_->slideshow_queue(), SIGNAL(finished_marketing()),
          &marketing_slide_timer_, SLOT(start()));
  connect(&marketing_slide_timer_, SIGNAL(timeout()),
        this, SLOT(queue_marketing_slide()));

  connect(settings_window_view_, SIGNAL(ok_button_pressed()),
          this, SLOT(gui_ok_button_pressed()));
  connect(settings_window_view_, SIGNAL(apply_button_pressed()),
          this, SLOT(gui_apply_button_pressed()));

  connect(settings_window_view_, SIGNAL(cancel_button_pressed()),
          this, SLOT(gui_cancel_button_pressed()));
  connect(&main_slide_timer_, SIGNAL(timeout()),
          this, SLOT(show_next_slide()));
  connect(settings_window_view_, SIGNAL(slide_folder_changed()),
          slideshow_data_model_->slideshow_queue(), SLOT(clear_queue()));
  connect(slideshow_window_view_, SIGNAL(about_slideshow_clicked()),
          this, SLOT(show_about_slideshow()));
  connect(slideshow_window_view_, SIGNAL(about_qt_clicked()),
          this, SLOT(show_about_qt()));

/*************************/

}

SlideshowController::~SlideshowController()
{
  slideshow_data_model_->deleteLater();
  slideshow_window_view_->deleteLater();
  settings_window_view_->deleteLater();
}

void SlideshowController::begin_slideshow()
{

  set_all_settings_to_default();
  ensure_folder_structure();
  parse_config_file(slideshow_data_model_->
                    config_file_path());
  if (slideshow_data_model_->fullscreen_disabled())
    {
      slideshow_window_view_->show();
    }
  else
    {
      // showFullscreen() seems to only work on linux and mac. For now, we
      // will emulate fullscreen with frameless maximized window so the app
      // doesn't break on windows.
      #ifdef Q_OS_WIN
        slideshow_window_view_->setWindowFlags(Qt::FramelessWindowHint);
        slideshow_window_view_->showMaximized();
      #else
        slideshow_window_view_->showFullScreen();
      #endif
    }
  if (slideshow_data_model_->begin_on_marketing())
    {
      queue_marketing_slide();
    }
  // Delay display of first slide to account for external
  // desktop effects
  int init_delay = slideshow_data_model_->init_delay_millisecs();
  QTimer::singleShot(init_delay, this, SLOT(show_next_slide()));
  main_slide_timer_.start(
        slideshow_data_model_->main_timer_interval());
  marketing_slide_timer_.start(
        slideshow_data_model_->marketing_timer_interval());
}

void SlideshowController::show_next_slide()
{

  Slide current_slide;

  parse_config_file(slideshow_data_model_->
                    config_file_path());
  build_slide_queue();

  // Check if image folder is empty
  if (slideshow_data_model_->slideshow_queue()->size() == 0)
    {
      slideshow_window_view_->display_no_images_error();
      return;
    }

  current_slide = slideshow_data_model_->
      slideshow_queue()->service();
  if (current_slide.slide_type() == IMAGE)
    {
      disconnect(&main_slide_timer_, SIGNAL(timeout()), this, SLOT(show_next_slide()));
      slideshow_window_view_->display_image(current_slide.full_path());
      connect(&main_slide_timer_, SIGNAL(timeout()),
          this, SLOT(show_next_slide()));
      main_slide_timer_.start(slideshow_data_model_->main_timer_interval());
    }
  else if (current_slide.slide_type() == VIDEO)
    {
      if (slideshow_data_model_->video_disabled())
        {
          main_slide_timer_.start(200);
          return;
        }
      // For some reason, this does not stop the timer
      // Disconnecting and reconnecting is a workaround
      main_slide_timer_.stop();
      marketing_slide_timer_.stop();
      slideshow_window_view_->display_video(current_slide.full_path());
      disconnect(&main_slide_timer_, SIGNAL(timeout()), this, SLOT(show_next_slide()));

    }
  qWarning() <<"[show]: " + current_slide.full_path();
}

void SlideshowController::queue_marketing_slide()
{
  slideshow_data_model_->slideshow_queue()->
      queue_marketing_slide();
}

void SlideshowController::set_all_settings_to_default()
{
  slideshow_data_model_->set_profile_folder(
        QStandardPaths::standardLocations(
          QStandardPaths::HomeLocation)[0]
          +"/SimpleSlideshow");
 slideshow_data_model_->set_image_folder(
       slideshow_data_model_->profile_folder_path()
       + "/slide_directory");
 slideshow_data_model_->set_config_file(
       slideshow_data_model_->profile_folder_path()
       + "/slideshow_display.conf");
 slideshow_data_model_->set_main_timer_interval(5000);
 slideshow_data_model_->set_marketing_timer_interval(50000);
 slideshow_data_model_->set_fullscreen_disabled(false);
 slideshow_data_model_->set_video_disabled(false);
 slideshow_data_model_->set_begin_on_marketing(true);
 slideshow_data_model_->slideshow_queue()->set_marketing_option(CONSECUTIVE);
 slideshow_data_model_->set_init_delay(100);

}

void SlideshowController::ensure_folder_structure()
{
  // Check for profile folder and create one if it does not exist
  if (!QDir(slideshow_data_model_->profile_folder_path()).exists())
    {
      QDir().mkdir(slideshow_data_model_->profile_folder_path());
    }
  if (!QDir(slideshow_data_model_->main_image_folder_path()).exists())
    {
      QDir().mkdir(slideshow_data_model_->main_image_folder_path());
    }
  // Check for config file and create one if it does not exist
  if (!QFile::exists(slideshow_data_model_->config_file_path()))
    {
       QFile config_file(slideshow_data_model_->config_file_path());
       if (config_file.open(QIODevice::ReadWrite))
         {
           QTextStream text_stream(&config_file);
           save_config_file(slideshow_data_model_->config_file_path());
         }
    }
   /* Qt automatically closes files in
    * this context.
    */
}

void SlideshowController::save_config_file(QString file_path)
{
  QFile config_file(file_path);
  if (config_file.open(QIODevice::WriteOnly))
    {
      QTextStream out_stream(&config_file);
      out_stream << "####### SimpleSlideshow Configuration #######"
                 << endl;
      out_stream << "display_timer_interval="
                 << slideshow_data_model_->main_timer_interval()
                 << endl;
      out_stream << "marketing_timer_interval="
                 << slideshow_data_model_->marketing_timer_interval()
                 << endl;
      out_stream << "fullscreen_disabled="
                 << slideshow_data_model_->fullscreen_disabled()
                 << endl;
      out_stream << "video_disabled="
                 << slideshow_data_model_->video_disabled()
                 << endl;
      out_stream << "main_slide_order="
                 << slideshow_data_model_->slideshow_queue()->
                    main_order_option()
                 << endl;
      out_stream << "marketing_slide_order="
                 << slideshow_data_model_->slideshow_queue()->
                    marketing_order_option()
                 << endl;
      out_stream << "marketing_playback_option="
                 << slideshow_data_model_->slideshow_queue()->
                    marketing_option()
                 << endl;
      out_stream << "begin_on_marketing_slide="
                 << slideshow_data_model_->begin_on_marketing()
                 << endl;
      out_stream << "init_delay="
                 << slideshow_data_model_->init_delay_millisecs()
                 << endl;
      config_file.close();
    }
}

// Refactor?
void SlideshowController::parse_config_file(QString file_path)
{
  QFile config_file(file_path);
  if (config_file.open(QIODevice::ReadOnly))
    {
      QTextStream stream(&config_file);

      // separate keys from values
      while (!stream.atEnd())
        {
          QString line;
          QString key, value_str;
          int line_index;
          int value_int;

          line = stream.readLine();

          // Check if line is a comment line
          if (line.at(0) == '#')
            {
              line = stream.readLine();
            }
          line_index = 0;
          while (line_index < line.size() && line.at(line_index) != '=')
            {
              key.append(line.at(line_index));
              ++line_index;
            }
          ++line_index;
          while (line_index < line.size())
            {
              value_str.append(line.at(line_index));
              ++line_index;
            }

          // update config settings
          if (key == "display_timer_interval")
            {
              bool value_is_integer;
              value_int = value_str.toInt(&value_is_integer);
              if (value_is_integer && value_int > 0)
                {
                  slideshow_data_model_->
                      set_main_timer_interval(value_int);
                }
              else
                {
                  warn_config_error(key, value_str);
                }
            }
          else if (key == "marketing_timer_interval")
            {
              bool value_is_integer;
              value_int = value_str.toInt(&value_is_integer);
              if (value_is_integer && value_int > 0)
                {
                  slideshow_data_model_->
                      set_marketing_timer_interval(value_int);
                }
              else
                {
                  warn_config_error(key, value_str);
                }
            }
          else if (key == "fullscreen_disabled")
            {
              bool value_is_integer;
              value_int = value_str.toInt(&value_is_integer);
              if (value_is_integer && value_int >= 0)
                {
                  slideshow_data_model_->set_fullscreen_disabled(value_int);
                }
              else
                {
                  warn_config_error(key, value_str);
                }
            }
          else if (key == "video_disabled")
            {
              bool value_is_integer;
              value_int = value_str.toInt(&value_is_integer);
              if (value_is_integer && value_int >= 0)
                {
                  slideshow_data_model_->set_video_disabled(value_int);
                }
              else
                {
                  warn_config_error(key, value_str);
                }
            }
          else if (key == "main_slide_order")
            {
              bool value_is_integer;
              value_int = value_str.toInt(&value_is_integer);
              if (value_is_integer && value_int >= 0)
                {
                  slideshow_data_model_->slideshow_queue()->
                      set_main_order((QueueSortOrder) value_int);
                }
              else
                {
                  warn_config_error(key, value_str);
                }
            }
            else if (key == "marketing_slide_order")
              {
                bool value_is_integer;
                value_int = value_str.toInt(&value_is_integer);
                if (value_is_integer && value_int >= 0)
                  {
                    slideshow_data_model_->slideshow_queue()->
                        set_marketing_order((QueueSortOrder) value_int);
                  }
                else
                  {
                    warn_config_error(key, value_str);
                  }
            }
          else if (key == "marketing_playback_option")
            {
              bool value_is_integer;
              value_int = value_str.toInt(&value_is_integer);
              if (value_is_integer && value_int >= 0)
                {
                  slideshow_data_model_->slideshow_queue()->
                      set_marketing_option((MarketingPlaybackOption) value_int);
                }
              else
                {
                  warn_config_error(key, value_str);
                }
          }
          else if (key == "begin_on_marketing_slide")
            {
              bool value_is_integer;
              value_int = value_str.toInt(&value_is_integer);
              if (value_is_integer && value_int >= 0)
                {
                  slideshow_data_model_->set_begin_on_marketing(value_int);
                }
              else
                {
                  warn_config_error(key, value_str);
                }
            }
          else if (key == "init_delay")
            {
              bool value_is_integer;
              value_int = value_str.toInt(&value_is_integer);
              if (value_is_integer && value_int >= 0)
                {
                  slideshow_data_model_->set_init_delay(value_int);
                }
              else
                {
                  warn_config_error(key, value_str);
                }
            }
        }
      config_file.close();
    }
}

void SlideshowController::export_settings_to_gui()
{
  settings_window_view_->set_main_timer_interval(
        slideshow_data_model_->main_timer_interval());
  settings_window_view_->set_marketing_timer_interval(
        slideshow_data_model_->marketing_timer_interval());
  settings_window_view_->set_fullscreen_disabled(
        slideshow_data_model_->fullscreen_disabled());
  settings_window_view_->set_slide_folder_path(
        slideshow_data_model_->main_image_folder_path());
  settings_window_view_->set_slide_directory_list(
        *slideshow_data_model_->slide_dir_list());
  settings_window_view_->set_up_gui();
  settings_window_view_->set_main_order(
        slideshow_data_model_->slideshow_queue()->
        main_order_option());
  settings_window_view_->set_marketing_order(
        slideshow_data_model_->slideshow_queue()->
        marketing_order_option());
  settings_window_view_->set_marketing_option(
        slideshow_data_model_->slideshow_queue()->
        marketing_option());
  settings_window_view_->set_begin_on_marketing_slide(
        slideshow_data_model_->begin_on_marketing());
  settings_window_view_->set_up_gui();
}

void SlideshowController::import_settings_from_gui()
{
  slideshow_data_model_->set_main_timer_interval(
        settings_window_view_->main_timer_interval());
  slideshow_data_model_->set_marketing_timer_interval(
        settings_window_view_->marketing_timer_interval());
  slideshow_data_model_->set_fullscreen_disabled(
        settings_window_view_->fullscreen_disabled());
  slideshow_data_model_->set_image_folder(
        settings_window_view_->slide_folder_path());
  slideshow_data_model_->slideshow_queue()->set_main_order(
        settings_window_view_->main_order_option());
  slideshow_data_model_->slideshow_queue()->set_marketing_order(
        settings_window_view_->marketing_order_option());
  slideshow_data_model_->slideshow_queue()->set_main_order(
        settings_window_view_->main_order_option());
  slideshow_data_model_->slideshow_queue()->set_marketing_option(
        settings_window_view_->marketing_option());
  slideshow_data_model_->set_begin_on_marketing(
        settings_window_view_->begin_on_marketing_slide_bool());
  this->save_config_file(
        slideshow_data_model_->config_file_path());
}


void SlideshowController::show_settings_view()
{
  export_settings_to_gui();
  settings_window_view_->show();
  settings_window_view_->raise();

}

void SlideshowController::show_about_slideshow()
{
  about_window_view_->show_about_slideshow();
}

void SlideshowController::show_about_qt()
{
  about_window_view_->show_about_qt();
}

void SlideshowController::gui_ok_button_pressed()
{
  import_settings_from_gui();
  build_slide_queue();
  settings_window_view_->close();
}

void SlideshowController::gui_cancel_button_pressed()
{
  settings_window_view_->close();
}

void SlideshowController::gui_apply_button_pressed()
{
  import_settings_from_gui();
  build_slide_queue();
  export_settings_to_gui();
}

void SlideshowController::post_video_unpause()
{
  this->show_next_slide();
}

void SlideshowController::warn_config_error(QString key, QString value_str)
{
  qWarning() << key << " - Invalid option: " <<
                value_str << ". Resetting to default";
}

void SlideshowController::refresh_directory_list()
{
  QDirIterator dir_iterator(slideshow_data_model_->main_image_folder_path(),
                            QDir::Dirs | QDir::NoSymLinks | 
                            QDir::Hidden);
  slideshow_data_model_->slide_dir_list()->clear();
  // Make sure profile folder exists
  ensure_folder_structure();

  // Iterate through main_image_folder to obtain
  // first-level subdirectories.  Add subdirectories
  // to a list
  if (QDir(slideshow_data_model_->main_image_folder_path()).
      entryList().size() == 2)
    {
      qWarning() << "Directory is empty.";
    }
  else
    {
      qWarning() << "Directory is not empty";
      while(dir_iterator.hasNext())
        {
          dir_iterator.next();
          if (dir_iterator.fileName() != "." && dir_iterator.fileName() !="..")
            {
              SlideDirectory temp;
              temp.set_dir_name(dir_iterator.fileName());

              temp.set_full_path(dir_iterator.fileInfo().absoluteFilePath());
              if (temp.name().contains("-info"))
                {
                  temp.set_marketing_folder(true);
                }
              if (temp.name().at(0) == '.')
                {
                  temp.set_exclude_from_show(true);
                }
              else
                {
                  temp.set_exclude_from_show(false);
                }
              slideshow_data_model_->slide_dir_list()->append(temp);
            }
        }
    }
  qWarning() << "[size2]: " << slideshow_data_model_->slide_dir_list()->size();
}

void SlideshowController::build_slide_queue()
{
  bool slides_were_added = false;

  refresh_directory_list();
  for (int i = 0;
       i < slideshow_data_model_->slide_dir_list()->size();
       ++i)
    {
      SlideDirectory current_dir = slideshow_data_model_->slide_dir_list()->value(i);
      QDirIterator subdir_iterator(current_dir.full_path(),
              QDir::Files | QDir::NoSymLinks | QDir::Hidden,
              QDirIterator::Subdirectories);
      //qWarning() << subdir_iterator.hasNext();
      while (subdir_iterator.hasNext())
        {
          subdir_iterator.next();
          Slide current_slide(subdir_iterator.filePath());
          if(current_dir.is_excluded())
            {
        //      qWarning () << "excluded";
              slideshow_data_model_->slideshow_queue()->
                  remove_key(current_slide.full_path());
            }
          else if (current_slide.slide_type() == INVALID_SLIDE)
            {
              // Do Nothing
              qWarning () << "INVALID SLIDE";
            }
          else if(current_dir.is_marketing_folder())
            {
      //        qWarning() << "marketing";
              if(slideshow_data_model_->slideshow_queue()->
                  add_marketing_slide(current_slide))
                {
                  slides_were_added = true;
                }
            }
          else
            {
        //      qWarning () << "slide";
              if (slideshow_data_model_->slideshow_queue()->
                  add_slide(current_slide))
                {
                  slides_were_added = true;
                }

            }
         // qWarning() <<"[i]: "<< subdir_iterator.filePath();
        }
    }

  // If slides were added to the queue, sort the lists
  if (slides_were_added)
    {
      slideshow_data_model_->slideshow_queue()->sort_all_lists();
    }
  qWarning() << slideshow_data_model_->slideshow_queue()->size();
}


