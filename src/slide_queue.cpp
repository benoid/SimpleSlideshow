#include "slide_queue.h"
#include "ansi_colors.h"

SlideQueue::SlideQueue(QObject *parent) : QObject(parent)
{
  this->info_slide_queued_ = true;
  this->main_queue_order_ = RANDOMIZED;
  this->info_playback_option_ = SESSION;
  this->main_session_length_ = 5;
  this->directory_refresh_rate_ms_ = 0;

 /* connect(&directory_refresh_timer_, SIGNAL(timeout()), this, SLOT(refresh_all_dirs()));
  connect(&directory_refresh_timer_, SIGNAL(timeout()), &directory_refresh_timer_,
          SLOT(start()));

  directory_refresh_timer_.setInterval(dir_refresh_rate_ms());
  directory_refresh_timer_.start(); */
}

Slide SlideQueue::private_service_main()
{
  /* Check if queue is empty. Push a "break" tag
   * so the queue knows to switch to the info queue
   */
  if (main_slide_queue_.size() == 0)
    main_slide_queue_.push_back(Slide("break"));

  Slide s = main_slide_queue_.front();
  main_slide_queue_.pop_front();
  if (s.exists())
    main_slide_queue_.push_back(s);
  if (s.file_path() == "break")
    {
      info_slide_queued_ = true;

      /* "break" tags can pile up when slides are removed from the queue.
       * Since the queue can be sorted in a myriad of ways, it is safer to
       * remove adjacent break tags than to attempt to keep track of removing
       * "break" tags for all possible sort orders.
       */
      while (main_slide_queue_.size() > 0 &&
             main_slide_queue_.front().file_path() == "break")
        main_slide_queue_.pop_front();
      main_slide_queue_.push_back(s);

    }
  return s;
}

Slide SlideQueue::private_service_info()
{
  /* Check if queue is empty. Push a "break" tag
   * so the queue knows to switch to the main queue
   */
  if (info_slide_queue_.size() == 0)
    info_slide_queue_.push_back(Slide("break"));
  Slide s = info_slide_queue_.front();
  info_slide_queue_.pop_front();
  if (s.exists())
    info_slide_queue_.push_back(s);
  if (s.file_path() == "break")
    {
      info_slide_queued_ = false;

      /* "break" tags can pile up when slides are removed from the queue.
       * Since the queue can be sorted in a myriad of ways, it is safer to
       * remove adjacent break tags than to attempt to keep track of removing
       * "break" tags for all possible sort orders.
       */
      while (info_slide_queue_.size() > 0 &&
             info_slide_queue_.first().file_path() == "break")
        info_slide_queue_.pop_front();
      info_slide_queue_.push_back(s);
    }
  return s;
}

void SlideQueue::assimilate_info_queue(QList<Slide> new_slide_list)
{
  if (new_slide_list.empty())
    return;

  qDebug () << "assimilating info";
  /*** ASSIMILATE SESSION ***/
  if (info_playback_option() == SESSION)
    {
      Slide front_slide;
      if (info_slide_queue_.size() > 0)
        front_slide = info_slide_queue_.front();
      else
        front_slide = new_slide_list.front();
      info_slide_queue_.clear();
      QStringList dir_list = this->dir_list();
      qDebug() <<  "inserting items";
      foreach (QString dir, dir_list)
        {
          if (info_directory_map_.contains(dir))
            {
              info_slide_queue_ << (*info_directory_map_.find(dir)).qList();
              info_slide_queue_.push_back(Slide("break"));
            }
        }
      while (info_slide_queue_.front().absolute_file_path() !=
             front_slide.absolute_file_path())
        {
          qDebug () << "ma: " << info_slide_queue_.front().absolute_file_path();
          qDebug () << "fr: " << front_slide.absolute_file_path();
          info_slide_queue_.push_back(info_slide_queue_.front());
          info_slide_queue_.pop_front();
        }
    }
  else if (info_queue_order() == INDIVIDUAL)
    {
      qDebug() << "in random";
      info_slide_queue_.removeAll(Slide("break"));
      srand((time(NULL)));
      while(!new_slide_list.empty())
      {
        if (info_slide_queue_.empty())
          {
            info_slide_queue_.push_back(new_slide_list.first());
          }
        else
          {
            int random_number = rand() % (info_slide_queue_.size());

            info_slide_queue_.insert(random_number, new_slide_list.first());
          }
        if (!new_slide_list.empty())
          new_slide_list.pop_front();

      }
      int init_size = info_slide_queue_.size();
      for (int i = 0; i < init_size; ++i)
        {
          info_slide_queue_.push_back(Slide("break"));
          info_slide_queue_.push_back(info_slide_queue_.first());
          info_slide_queue_.pop_front();
        }

    }
  qDebug () << "end assimilate info";
}

void SlideQueue::assimilate_main_queue(QList<Slide> new_slide_list)
{
  if (new_slide_list.empty())
    return;

  qDebug () << "assimilating main";
  /*** ASSIMILATE RANDOMLY ***/
  if (main_queue_order() == RANDOMIZED)
    {
      qDebug() << "in random";
     main_slide_queue_.removeAll(Slide("break"));
      srand((time(NULL)));
      while(!new_slide_list.empty())
      {
        if (main_slide_queue_.empty())
          {
            main_slide_queue_.push_back(new_slide_list.first());
          }
        else
          {
            int random_number = rand() % (main_slide_queue_.size());

            main_slide_queue_.insert(random_number, new_slide_list.first());
          }
        if (!new_slide_list.empty())
          new_slide_list.pop_front();

      }
  qDebug () << "end random";
    }
  /*** END ASSIMILATE RANDOMLY ***/

  /*** ASSIMILATE DIRECTORIES ***/
  else if (main_queue_order() == DIRECTORIES)
    {
      Slide front_slide;
      if (main_slide_queue_.size() > 0)
        front_slide = main_slide_queue_.front();
      else
        front_slide = new_slide_list.front();
      main_slide_queue_.clear();
      QStringList dir_list = this->dir_list();
      foreach (QString dir, dir_list)
        {
          if (slide_directory_map_.contains(dir))
            main_slide_queue_ << (*slide_directory_map_.find(dir)).qList();
        }
      while (main_slide_queue_.front().absolute_file_path() !=
             front_slide.absolute_file_path())
        {
          main_slide_queue_.push_back(main_slide_queue_.front());
          main_slide_queue_.pop_front();
        }


    }
  /*** END ASSIMILATE DIRECTORIES ***/

  /*** INSERT BREAK TAGS ***/
  Slide front_slide = main_slide_queue_.front();
  int i = 0;
  int init_size = main_slide_queue_.size();
  do
    {
      if (((i + main_session_length()) % (this->main_session_length_+1)) == 0)
        main_slide_queue_.push_back(Slide("break"));
      main_slide_queue_.push_back(main_slide_queue_.first());
      main_slide_queue_.pop_front();
      ++i;
    } while (i < init_size );//&& main_slide_queue_.first().absolute_file_path() !=
             //front_slide.absolute_file_path());
  /*** END INSERT BREAK TAGS ***/

}



void SlideQueue::set_main_queue_order(QueueSortOrder order)
{
  main_queue_order_= order;
}

QueueSortOrder SlideQueue::main_queue_order()
{
  return main_queue_order_;
}

void SlideQueue::set_info_queue_order(QueueSortOrder order)
{
  info_queue_order_ = order;
}

QueueSortOrder SlideQueue::info_queue_order()
{
  return info_queue_order_;
}

void SlideQueue::set_main_session_length(int length)
{
  main_session_length_ = length;
}

int SlideQueue::main_session_length()
{
  if (main_session_length_ < main_slide_queue_.size())
    return main_slide_queue_.size();
  else
    return main_session_length_;
}

void SlideQueue::set_info_playback_option(InfoPlaybackOption option)
{
  info_playback_option_ = option;
}

InfoPlaybackOption SlideQueue::info_playback_option()
{
  return info_playback_option_;
}

void SlideQueue::queue_info_slide()
{
  info_slide_queued_ = true;
}

void SlideQueue::add_slide_directory(QString dir_path)
{
  QString absolute_dir_path = QDir(dir_path).absolutePath();
  if (!QDir(absolute_dir_path).exists())
    {
      qDebug () << DEBUG_CONSOLE_WARNING_COLOR << " Warning:\n" <<
                   DEBUG_CONSOLE_DEFAULT_COLOR <<
                   "\tDirectory: " << absolute_dir_path <<
                   "does not exist. \n\tSkipping\n...";
      return;
    }
  if (this->contains_dir(absolute_dir_path))
    return;
  if (absolute_dir_path.contains("-info"))
    info_directory_map_.insert(absolute_dir_path, SlideDirectory(absolute_dir_path));
  else
    slide_directory_map_.insert(absolute_dir_path, SlideDirectory(absolute_dir_path));
}

bool SlideQueue::contains_dir(QString dir_path)
{
  if (slide_directory_map_.contains(QDir(dir_path).absolutePath()))
    return true;
  else if (info_directory_map_.contains(QDir(dir_path).absolutePath()))
    return true;
  return false;
  
}

void SlideQueue::remove_slide_directory(QString dir_path)
{
  QString absolute_dir_path = QDir(dir_path).absolutePath();
  slide_directory_map_.remove(absolute_dir_path);
  info_directory_map_.remove(absolute_dir_path);
}

void SlideQueue::set_dir_refresh_rate_ms(int ms)
{
  if (ms >= 0)
    directory_refresh_rate_ms_ = ms;
}

int SlideQueue::dir_refresh_rate_ms()
{
  return directory_refresh_rate_ms_;
}

bool SlideQueue::contains_slide(Slide s)
{
  QString slide_dir = QFileInfo(s.file_path()).absolutePath();
  if (SlideDirectory(slide_dir).is_informational())
    {
      if (!info_directory_map_.contains(slide_dir))
       return false;
      return info_directory_map_.find(slide_dir).value().contains(s);
    }
  else
    {
      if (!slide_directory_map_.contains(slide_dir))
       return false;
      return slide_directory_map_.find(slide_dir).value().contains(s);
    }
}

void SlideQueue::remove_slide(Slide s)
{
  QString slide_dir = QFileInfo(s.file_path()).absolutePath();
  if (SlideDirectory(slide_dir).is_informational())
    {
      info_slide_queue_.removeAll(s);
    }
  else
    {
      main_slide_queue_.removeAll(s);
    }
}

QStringList SlideQueue::dir_list()
{
  QStringList l;
  QMap<QString, SlideDirectory>::iterator itr;
  if (slide_directory_map_.size() > 0)
    for (itr = slide_directory_map_.begin(); itr != slide_directory_map_.end(); ++itr)
      {
        SlideDirectory* sd = &(*itr);
        l << sd->dir_path();
      }
  if (info_directory_map_.size() > 0)
    for (itr = info_directory_map_.begin(); itr != info_directory_map_.end(); ++itr)
      {
        SlideDirectory* sd = &(*itr);
        l << sd->dir_path();
      }
    return l;
}

int SlideQueue::num_dirs()
{
  return slide_directory_map_.size() + info_directory_map_.size();
}

int SlideQueue::size()
{
  return main_queue_size() + info_queue_size();
}

int SlideQueue::main_queue_size()
{
  QStringList dir_list = this->dir_list();
  int size = 0;
  foreach (QString dir, dir_list)
    {
      if (slide_directory_map_.contains(dir))
        {
          size += slide_directory_map_.find(dir).value().size();
        }
    }
  return size;
}

int SlideQueue::info_queue_size()
{
  QStringList dir_list = this->dir_list();
  int size = 0;
  foreach (QString dir, dir_list)
    {
      if (info_directory_map_.contains(dir))
        {
          size += info_directory_map_.find(dir).value().size();
        }
    }
  return size;
}

void SlideQueue::refresh_all_dirs()
{
  QMap<QString, SlideDirectory>::iterator itr;
  QList<Slide> new_slide_list_main, new_slide_list_info;
  if (slide_directory_map_.size() > 0)
    for (itr = slide_directory_map_.begin(); itr != slide_directory_map_.end(); ++itr)
      {
        SlideDirectory* sd = &(*itr);
        new_slide_list_main << sd->refresh_contents();
      }
  qDebug () << "refreshing info";
  if (info_directory_map_.size() > 0)
    for (itr = info_directory_map_.begin(); itr != info_directory_map_.end(); ++itr)
      {
        qDebug () << "in r info loop";
        SlideDirectory* sd = &(*itr);
        new_slide_list_info << sd->refresh_contents();
      }
  qDebug () << "finished refreshing dirs. assimilating...";
  assimilate_main_queue(new_slide_list_main);
  assimilate_info_queue(new_slide_list_info);
}

Slide SlideQueue::service()
{
  this->refresh_all_dirs();
  if (this->size() == 0)
    return Slide("NULL");
  Slide s;
  while (!s.is_valid())
    {
      if (info_slide_queued_)
        s = private_service_info();
      else
        s = private_service_main();
    }

  return s;
}
