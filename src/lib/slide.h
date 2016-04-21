#ifndef SLIDE_H
#define SLIDE_H

#include <QString>
#include <QFileInfo>

enum SlideType
{
  INVALID_SLIDE = 0, IMAGE, VIDEO
};

class Slide
{
private:
  QString file_path_;
public:
  Slide();
  Slide(QString file_path);

  QString file_path();
  QString absolute_file_path();
  SlideType slide_type();
  bool is_valid();
  bool exists();

  void set_file_path(QString file_path);




};

#endif // SLIDE_H
