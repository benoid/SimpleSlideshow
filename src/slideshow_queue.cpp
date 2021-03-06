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

/* slideshow_queue.cpp

   Author: David Benoit
   Purpose: Implementation of the SlideshowQueue class. */

#include <QDir>
#include <QDebug>
#include <cstdlib> // for rand()
#include <ctime> // for time()
#include "slideshow_queue.h"

SlideshowQueue::SlideshowQueue(QObject *parent) : QObject(parent)
{
  queue_marketing_slide_ = 0;
  main_queue_index_ = 0;
  marketing_queue_index_ = 0;
  main_sort_order_ = (QueueSortOrder) 0;
  marketing_sort_order_ = (QueueSortOrder) 0;
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

int SlideshowQueue::add_slide(QString path, SlideType type)
{
  if (!slide_map_.contains(path))
    {
      slide_map_.insert(path, type);
      main_image_list_.append(path);

      // Slide was added
      return 1;
    }
  // Slide was not added
  return 0;
}

int SlideshowQueue::add_slide(Slide slide)
{
  if (!slide_map_.contains(slide.full_path()))
    {
      slide_map_.insert(slide.full_path(), slide.slide_type());
      main_image_list_.append(slide.full_path());
      // Slide was added
      return 1;
    }
  // Slide was not added
  return 0;
}

int SlideshowQueue::add_marketing_slide(QString path, SlideType type)
{
  if (!slide_map_.contains(path))
    {
      slide_map_.insert(path, type);
      marketing_image_list_.append(path);
      // Slide was added
      return 1;
    }
  // Slide was not added
  return 0;
}

int SlideshowQueue::add_marketing_slide(Slide slide)
{
  if (!slide_map_.contains(slide.full_path()))
    {
      slide_map_.insert(slide.full_path(), slide.slide_type());
      marketing_image_list_.append(slide.full_path());
      // Slide was added
      return 1;
    }
  // Slide was not added
  return 0;
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

void SlideshowQueue::set_marketing_option(MarketingPlaybackOption option)
{
  marketing_playback_option_ = option;
}

QueueSortOrder SlideshowQueue::main_order_option()
{
  return main_sort_order_;
}

QueueSortOrder SlideshowQueue::marketing_order_option()
{
  return marketing_sort_order_;
}

MarketingPlaybackOption SlideshowQueue::marketing_option()
{
  return marketing_playback_option_;
}

bool SlideshowQueue::marketing_queued()
{
  return queue_marketing_slide_;
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

void SlideshowQueue::sort_all_lists()
{
  sort_list(&main_image_list_, main_sort_order_);
  sort_list(&marketing_image_list_, marketing_sort_order_);
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
  if (main_image_list_.size() <= 0 && marketing_image_list_.size() >= 0)
    {
      queue_marketing_slide_ = true;

    }
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

      else if (marketing_queue_index_ < marketing_image_list_.size() -1)
        {
          QString next_slide_path = marketing_image_list_.value(
                marketing_queue_index_ + 1);
          QString current_slide_dir = QFileInfo(current_slide.full_path()).
                                       absoluteDir().absolutePath();
          QString next_slide_dir = QFileInfo(next_slide_path).absoluteDir().
                                       absolutePath();
          if (current_slide_dir != next_slide_dir)
            {
              queue_marketing_slide_ = false;
              emit finished_marketing();
            }
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

