/*    Copyright (C) 2016 David Benoit

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

/* queue_sort_order.h

   Author: David Benoit
   Purpose: Create enumerated types representing
           options for slide playback and sorting. */
  
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

