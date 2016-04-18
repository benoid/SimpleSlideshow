#ifndef SLIDEDIRECTORY_H
#define SLIDEDIRECTORY_H

#include <QString>
#include <QDebug>
#include <QSet>
#include <QDir>
#include <QHash>
#include <QDirIterator>
#include <QList>
#include "./slide.h"
#include "ansi_colors.h"

inline uint qHash(Slide s)
{
  return qHash(s.absolute_file_path());
}

inline bool operator==(Slide a, Slide b)
{
  return a.file_path() == b.file_path();
}

typedef QSet<Slide>::iterator SlideDirectoryIterator;

class SlideDirectory
{
private:
  QSet<Slide> slide_set_;
  QString dir_path_;
  void insert(Slide s);
  void remove(Slide s);
  void purge_nonexistant_entries();
  friend class SlideDirectoryTests;
public:
  SlideDirectory(QString dir_path);

  bool is_informational();

  void build_from_local_dir();
  QList<Slide> refresh_contents();


  QList<Slide> qList();

  bool contains(Slide s);

  SlideDirectoryIterator begin();
  SlideDirectoryIterator end();

  QString dir_path();

  int size();
};



#endif // SLIDEDIRECTORY_H
