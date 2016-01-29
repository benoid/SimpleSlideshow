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

  // Delay display of first slide to account for external
  // desktop effects
  int init_delay_ms_;

};

#endif // SLIDESHOWDATAMODEL_H
