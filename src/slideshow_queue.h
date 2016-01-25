/* slideshow_controller.h
 *
 * Author: David Benoit
 * Purpose: Container class representing a queue of slides.
 *          Responsible for storing Slide objects and
 *          determining which slide to display next.
 *          Stores information about slides as QStringLists
 *          for ordering purpose, and creates a QMap of
 *          slides for quick lookups, which the application
 *          performs whenever the filesystem is parsed
 *          (very often)
 */

#ifndef SLIDESHOWQUEUE_H
#define SLIDESHOWQUEUE_H

#include <QObject>
#include <QMap>
#include <QMapIterator>
#include <QDir>
#include <QDebug>
#include <QStringList>
#include <cstdlib> // for rand()
#include <ctime> // for time()

#include "slide.h"
#include "queue_sort_order.h"



class SlideshowQueue : public QObject
{
  Q_OBJECT
public:
  explicit SlideshowQueue(QObject *parent = 0);

  // Returns the next Slide object in the queue
  // and increments the index
  Slide service();

  // Creates a slide from the file path and slide type
  // and adds it to the main queue
  void add_slide(QString path, SlideType type);

  // Copies a slide and adds it to the main queue
  void add_slide(Slide slide);

  // Creates a slide from the file path and slide type
  // and adds it to the marketing queue
  void add_marketing_slide(QString path, SlideType type);

  // Copies a slide and adds it to the main queue
  void add_marketing_slide(Slide slide);

  // Returns true if queue contains a
  // slide whose path matches the key
  bool contains(QString key);

  // Removes a slide whose path matches the key
  void remove_key(QString key);

  // Sets queue_marketing_slide_ = true
  void queue_marketing_slide();

  // Returns the number of slides in the queue
  int size();

  //Mutators
  void set_marketing_order(QueueSortOrder option);
  void set_main_order(QueueSortOrder option);
  void set_marketing_option(MarketingPlaybackOption option){
    marketing_playback_option_ = option;}

  // Accessors
  QueueSortOrder main_order_option(){
    return main_sort_order_;}
  QueueSortOrder marketing_order_option(){
    return marketing_sort_order_;}
  MarketingPlaybackOption marketing_option(){return marketing_playback_option_;}



signals:
  void finished_marketing();

public slots:
  // Clears contents of queue
  void clear_queue();


private:
  // Slide map to provide quick lookups
  QMap<QString, SlideType> slide_map_;


  // List of main slides
  QStringList main_image_list_;

  // Stores index of current regular slide
  int main_queue_index_;

  // List of marketing slides
  QStringList marketing_image_list_;
  // Stores index of current marketing slide
  int marketing_queue_index_;

  // Determines whether the current slide
  // is regular or marketing
  bool queue_marketing_slide_;

  // Stores desired way to sort the
  // main queue
  QueueSortOrder main_sort_order_;

  // Stores desired way to sort the
  // marketing queue
  QueueSortOrder marketing_sort_order_;

  // Stores the desired way to
  // Play the contents of the marketing folder
  MarketingPlaybackOption marketing_playback_option_;

/*** Private Member Functions ***/

  // Called by public function service.
  // Decides whether to queue regular or
  // marketing slide.  Removes slides
  // from queue if they do not exist on
  // filesystem (eg. have been deleted
  // by the user)
  Slide private_service();

  // Driver for sort functions
  void sort_list(QStringList *list, QueueSortOrder order);

  // Takes a QstringList and sorts it alpha-numerically
  void alpha_sort(QStringList *list);

  // Takes a QstringList and sorts it reverse alpha-numerically
  void reverse_alpha_sort(QStringList *list);

  // Takes a QStringList and randomizes its contents
  void randomize(QStringList *list);


};

#endif // SLIDESHOWQUEUE_H
