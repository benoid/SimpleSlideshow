/* slideshow_data_model.cpp
 *
 * Author: David Benoit
 * Purpose: Implementation of the SlideshowDataModel class
 */

#include "slideshow_data_model.h"

SlideshowDataModel::SlideshowDataModel(QObject *parent) : QObject(parent)
{
  slideshow_queue_ = new SlideshowQueue;
}

SlideshowDataModel::~SlideshowDataModel()
{
  slideshow_queue_->deleteLater();
}

void SlideshowDataModel::set_profile_folder(QString folder)
{
  profile_folder_path_ = folder;
}

void SlideshowDataModel::set_image_folder(QString folder)
{
  main_image_folder_path_ = folder;
}

void SlideshowDataModel::set_main_timer_interval(int millisecs)
{
  main_timer_interval_ = millisecs;
}

void SlideshowDataModel::set_marketing_timer_interval(int millisecs)
{
  marketing_timer_interval_ = millisecs;
}

void SlideshowDataModel::set_fullscreen_disabled(bool set)
{
  fullscreen_disabled_bool_ = set;
}

void SlideshowDataModel::set_config_file(QString file)
{
  config_file_path_ = file;
}

void SlideshowDataModel::set_video_disabled(bool set)
{
  video_disabled_ = set;
}

void SlideshowDataModel::set_begin_on_marketing(bool set)
{
  begin_on_marketing_ = set;
}

void SlideshowDataModel::set_init_delay(int num_millisecs)
{
  init_delay_ms_ = num_millisecs;
}

SlideshowQueue *SlideshowDataModel::slideshow_queue()
{
  return slideshow_queue_;
}

QString SlideshowDataModel::profile_folder_path()
{
  return profile_folder_path_;
}

QString SlideshowDataModel::main_image_folder_path()
{
  return main_image_folder_path_;
}

QString SlideshowDataModel::config_file_path()
{
  return config_file_path_;
}

QList<SlideDirectory> *SlideshowDataModel::slide_dir_list()
{
  return &slide_dir_list_;
}

int SlideshowDataModel::main_timer_interval()
{
  return main_timer_interval_;
}

int SlideshowDataModel::marketing_timer_interval()
{
  return marketing_timer_interval_;
}

bool SlideshowDataModel::fullscreen_disabled()
{
  return fullscreen_disabled_bool_;
}

bool SlideshowDataModel::video_disabled()
{
  return video_disabled_;
}

bool SlideshowDataModel::begin_on_marketing()
{
  return begin_on_marketing_;
}

int SlideshowDataModel::init_delay_millisecs()
{
  return init_delay_ms_;
}

