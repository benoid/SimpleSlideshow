/* slideshow_data_model.h
 *
 * Author: David Benoit
 * Purpose: Container class which stores all
 *          configureable settings.  Is responsible for
 *          creating and managing a SlideshowQueue
 *          object.
 */

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

/*** Mutators ***/
  void set_profile_folder(QString folder){
    profile_folder_path_ = folder;}
  void set_image_folder(QString folder){
    main_image_folder_path_ = folder;}
  void set_main_timer_interval(int millisecs){
    main_timer_interval_ = millisecs;}
  void set_marketing_timer_interval(int millisecs){
    marketing_timer_interval_ = millisecs;}
  void set_fullscreen_disabled(bool set){
    fullscreen_disabled_bool_ = set;}
  void set_config_file(QString file){config_file_path_ = file;}
  void set_video_disabled(bool set){video_disabled_ = set;}
  void set_begin_on_marketing(bool set){begin_on_marketing_ = set;}

/*** Accessors ***/
  SlideshowQueue * slideshow_queue(){return slideshow_queue_;}
  QString profile_folder_path(){return profile_folder_path_;}
  QString main_image_folder_path(){return main_image_folder_path_;}
  QString config_file_path(){return config_file_path_;}
  QList<SlideDirectory> * slide_dir_list(){return &slide_dir_list_;}
  int main_timer_interval(){return main_timer_interval_;}
  int marketing_timer_interval(){return marketing_timer_interval_;}
  bool fullscreen_disabled(){return fullscreen_disabled_bool_;}
  bool video_disabled(){return video_disabled_;}
  bool begin_on_marketing(){return begin_on_marketing_;}

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

  // True if fullscreen display is disabled
  bool fullscreen_disabled_bool_;

  // True if video playback is disabled
  bool video_disabled_;

  // True means a marketing slide will be queued
  // on application startup
  bool begin_on_marketing_;

};

#endif // SLIDESHOWDATAMODEL_H
