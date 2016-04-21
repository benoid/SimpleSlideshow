#ifndef SLIDEQUEUE_H
#define SLIDEQUEUE_H

#include <random>
#include <QObject>
#include <QSet>
#include <QString>
#include <QDir>
#include <QTimer>

#include "slide_directory.h"
#include "slide.h"

enum QueueSortOrder
{
  DIRECTORIES, RANDOMIZED
};

enum InfoPlaybackOption
{
  INDIVIDUAL, SESSION
};

class SlideQueue : public QObject
{
  Q_OBJECT
private:
  QMap<QString, SlideDirectory> slide_directory_map_;
  QMap<QString, SlideDirectory> info_directory_map_;

  QList<Slide> main_slide_queue_;
  QList<Slide> info_slide_queue_;

  Slide private_service_main();
  Slide private_service_info();

  InfoPlaybackOption info_playback_option_;

  bool info_slide_queued_;
  int main_session_length_;

  QueueSortOrder main_queue_order_;
  QueueSortOrder info_queue_order_;

  QTimer directory_refresh_timer_;
  int directory_refresh_rate_ms_;


/* IMPLEMENT */
  void assimilate_main_queue(QList<Slide> new_slide_list);
  void assimilate_info_queue(QList<Slide> new_slide_list);

  void sort_main_queue();
  void sort_info_queue();
/* END */

public:
  explicit SlideQueue(QObject *parent = 0);

  void set_main_queue_order(QueueSortOrder order);

  QueueSortOrder main_queue_order();

  void set_info_queue_order(QueueSortOrder order);

  QueueSortOrder info_queue_order();

  void set_main_session_length(int length);

  int main_session_length();

  void set_info_playback_option(InfoPlaybackOption option);

  InfoPlaybackOption info_playback_option();

  void queue_info_slide();

  void add_slide_directory(QString dir_path);

  bool contains_dir(QString dir_path);

  void remove_slide_directory(QString dir_path);
  void set_dir_refresh_rate_ms(int ms);
  int dir_refresh_rate_ms();

  bool contains_slide(Slide s);
  void remove_slide(Slide s);
  QStringList dir_list();

  int num_dirs();

  int size();
  int main_queue_size();
  int info_queue_size();

  Slide service();

  friend class SlideQueueTests;
signals:

public slots:
  void refresh_all_dirs();
};

#endif // SLIDEQUEUE_H
