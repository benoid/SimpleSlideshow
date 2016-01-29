/* slide_directory.h
 * 
 * Author: David Benoit
 * Purpose: Container class representing 
 *          a directory of slides.  Stores
 *          information about the name, file path,
 *          whether the directory contains informational/
 *          marketing slides, and whether the user has chosen 
 *          to exclude the directory from the slideshow
 */

#ifndef SLIDEDIRECTORY_H
#define SLIDEDIRECTORY_H

#include <QString>
#include <QStringList>

class SlideDirectory
{


public:
  SlideDirectory();
/*** Accessors ***/
  QString name();
  QString full_path();
  QStringList file_list();
  bool is_marketing_folder();
  bool is_excluded();

/*** Mutators ***/
  void set_dir_name(QString set_name);
  void set_full_path(QString set_path);
  void append_file_list(QString file);
  void set_marketing_folder(bool set_marketing_bool);
  void set_exclude_from_show(bool set_exclude_bool);
private:
  QString name_;
  QString full_path_;
  QStringList file_list_;
  bool marketing_folder_;
  bool exclude_from_slideshow_;

};

#endif // SLIDEDIRECTORY_H
