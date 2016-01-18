#ifndef SLIDEDIRECTORY_H
#define SLIDEDIRECTORY_H

#include <QString>
#include <QStringList>

class SlideDirectory
{


public:
  SlideDirectory();
/*** Accessors ***/
  QString name(){return name_;}
  QString full_path(){return full_path_;}
  QStringList file_list(){return file_list_;}
  bool is_marketing_folder(){return marketing_folder_;}
  bool is_excluded(){return exclude_from_slideshow_;}

/*** Mutators ***/
  void set_dir_name(QString set_name){name_ = set_name;}
  void set_full_path(QString set_path){full_path_ = set_path;}
  void append_file_list(QString file){file_list_.append(file);}
  void set_marketing_folder(bool set_marketing_bool){
    marketing_folder_ = set_marketing_bool;}
  void set_exclude_from_show(bool set_exclude_bool){
    exclude_from_slideshow_ = set_exclude_bool;}
private:
  QString name_;
  QString full_path_;
  QStringList file_list_;
  bool marketing_folder_;
  bool exclude_from_slideshow_;

};

#endif // SLIDEDIRECTORY_H
