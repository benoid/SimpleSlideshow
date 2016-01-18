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
  void set_full_path(QString path){full_path_ = path;}
  void set_slide_type(SlideType type){slide_type_ = type;}


/*** Accessors ***/
  QString full_path(){return full_path_;}
  SlideType slide_type(){return slide_type_;}

private:
  QString full_path_;
  SlideType slide_type_;

  SlideType get_slide_type(QString path);
};

#endif // SLIDE_H
