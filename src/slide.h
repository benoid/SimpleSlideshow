/* slide.h
 * 
 * Author: David Benoit
 * Purpose: Container class representing 
 *          a slideshow slide.  Stores
 *          file path and slide type
 *          (IMAGE, VIDEO, or NULL_SLIDE)
 */

#ifndef SLIDE_H
#define SLIDE_H

#include <QString>
#include <QFileInfo>
#include <QDebug>

enum SlideType
{
  NULL_SLIDE,IMAGE, VIDEO, INVALID_SLIDE
};

class Slide
{
public:
  Slide();
  Slide(QString path, SlideType type);
  Slide(QString path);

/*** Mutators ***/
  void set_full_path(QString path);
  void set_slide_type(SlideType type);


/*** Accessors ***/
  QString full_path();
  SlideType slide_type();

private:
  QString full_path_;
  SlideType slide_type_;

  SlideType get_slide_type(QString path);
};

#endif // SLIDE_H
