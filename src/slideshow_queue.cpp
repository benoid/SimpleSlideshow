/* slideshow_queue.cpp
 *
 * Author: David Benoit
 * Purpose: Implementation of the SlideshowQueue class
 */

#include "slideshow_queue.h"

SlideshowQueue::SlideshowQueue(QObject *parent) : QObject(parent)
{
  queue_marketing_slide_ = 0;
  main_queue_index_ = 0;
  marketing_queue_index_ = 0;
}

Slide SlideshowQueue::service()
{
  Slide current_slide;
  current_slide = private_service();
  while (current_slide.slide_type() == NULL_SLIDE)
    {
      current_slide = private_service();
    }
  return current_slide;
}

void SlideshowQueue::add_slide(QString path, SlideType type)
{
  if (!slide_map_.contains(path))
    {
      slide_map_.insert(path, type);
      main_image_list_.append(path);
    }
}

void SlideshowQueue::add_slide(Slide slide)
{
  if (!slide_map_.contains(slide.full_path()))
    {
      slide_map_.insert(slide.full_path(), slide.slide_type());
      main_image_list_.append(slide.full_path());
    }
}

void SlideshowQueue::add_marketing_slide(QString path, SlideType type)
{
  if (!slide_map_.contains(path))
    {
      slide_map_.insert(path, type);
      marketing_image_list_.append(path);
    }
}

void SlideshowQueue::add_marketing_slide(Slide slide)
{
  if (!slide_map_.contains(slide.full_path()))
    {
      slide_map_.insert(slide.full_path(), slide.slide_type());
      marketing_image_list_.append(slide.full_path());
    }
}

void SlideshowQueue::set_marketing_order(QueueSortOrder option)
{
  if (marketing_sort_order_ != option)
      {
        marketing_sort_order_ = option;
        sort_list(&marketing_image_list_, marketing_sort_order_);
      }
}

void SlideshowQueue::set_main_order(QueueSortOrder option)
{
  if (main_sort_order_ != option)
    {
      main_sort_order_ = option;
      sort_list(&main_image_list_, main_sort_order_);
    }
  qWarning() << main_image_list_;
}

bool SlideshowQueue::contains(QString key)
{
  if (slide_map_.contains(key))
    return true;
  else
    return false;
}

void SlideshowQueue::remove_key(QString key)
{
  if (slide_map_.contains(key))
    {
      int index = main_image_list_.indexOf(key);
      if (index < 0)
        {
          index = marketing_image_list_.indexOf(key);
          if (index >= 0)
            marketing_image_list_.removeAt(index);
        }
      else
        {
          main_image_list_.removeAt(index);
        }
      slide_map_.remove(key);

    }
}

void SlideshowQueue::queue_marketing_slide()
{
  queue_marketing_slide_ = true;
}

int SlideshowQueue::size()
{
  return slide_map_.size();
}

void SlideshowQueue::clear_queue()
{
  slide_map_.clear();
  main_image_list_.clear();
  marketing_image_list_.clear();
  main_queue_index_ = 0;
  marketing_queue_index_ = 0;

}

Slide SlideshowQueue::private_service()
{
  Slide current_slide;
  if (queue_marketing_slide_)
    {
      if (marketing_queue_index_ < marketing_image_list_.size())
        {
          current_slide.set_full_path(marketing_image_list_.value(
                                        marketing_queue_index_));
          current_slide.set_slide_type(slide_map_.value(
                                       current_slide.full_path()));
          ++marketing_queue_index_;
        }
      if (marketing_queue_index_ >= marketing_image_list_.size())
        {
          marketing_queue_index_ = 0;
          queue_marketing_slide_ = false;
          emit finished_marketing();
        }
      else if (marketing_playback_option_ == DISPERSED)
        {
          queue_marketing_slide_ = false;
          emit finished_marketing();
        }
      if (!QFile(current_slide.full_path()).exists())
        {
          current_slide.set_slide_type(NULL_SLIDE);
          this->remove_key(current_slide.full_path());
        }
      //qWarning() << "[m.size]: " << marketing_image_list_.size();
    }
  else
    {
      //  Implement
      if (main_queue_index_ < main_image_list_.size())
        {
          current_slide.set_full_path(main_image_list_.value(
                                        main_queue_index_));
          current_slide.set_slide_type(slide_map_.value(
                                       current_slide.full_path()));
          ++main_queue_index_;
        }
      if (main_queue_index_ >= main_image_list_.size())
        {
          main_queue_index_ = 0;
        }

      if (!QFile(current_slide.full_path()).exists())
        {
          current_slide.set_slide_type(NULL_SLIDE);
          this->remove_key(current_slide.full_path());
        }
    }
  return current_slide;
}

void SlideshowQueue::sort_list(QStringList *list, QueueSortOrder order)
{
  switch (order)
    {
    case UNSORTED:
      break;

    case ALPHA_NUMERIC:
      alpha_sort(list);
      break;

    case REVERSE_ALPHA_NUMERIC:
      reverse_alpha_sort(list);
      break;
    case RANDOMIZED:
      randomize(list);
      break;

    }
}

void SlideshowQueue::alpha_sort(QStringList *list)
{
  list->sort(Qt::CaseInsensitive);
}

void SlideshowQueue::reverse_alpha_sort(QStringList *list)
{
  QStringList temp;
  list->sort(Qt::CaseInsensitive);

  for (int i = list->size() - 1; i >= 0; --i)
    {
      temp.append(list->at(i));
    }
  //list->clear();
  *list = temp;

}

void SlideshowQueue::randomize(QStringList *list)
{
  QStringList temp;
  int random_index;
  srand(time(NULL));
  while (list->size() > 0)
    {
      random_index = rand() % list->size();
      temp.append(list->takeAt(random_index));
    }
  list->clear();
  *list = temp;
}

