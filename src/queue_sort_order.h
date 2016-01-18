/* queue_sort_order.h
 *
 * Author: David Benoit
 * Purpose: Create enumerated types representing
 *          options for slide playback and sorting
 */
  
#ifndef QUEUE_SORT_ORDER_H
#define QUEUE_SORT_ORDER_H

// Enumerated type representing
// options for sorting the slideshow
// queue
enum QueueSortOrder
{
  UNSORTED, ALPHA_NUMERIC, REVERSE_ALPHA_NUMERIC,
  RANDOMIZED
};


// Enumerated type representing
// options for marketing
// slide playback
enum MarketingPlaybackOption
{
  DISPERSED, CONSECUTIVE
};

#endif // QUEUE_SORT_ORDER_H

