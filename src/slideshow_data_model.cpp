#include "slideshow_data_model.h"

SlideshowDataModel::SlideshowDataModel(QObject *parent) : QObject(parent)
{
  slideshow_queue_ = new SlideshowQueue;
}

