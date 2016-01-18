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

