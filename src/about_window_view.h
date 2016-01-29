/*  Copyright (C) 2016 David Benoit

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

/* about_window_view.h

    Author: David Benoit
    Purpose: Display a window with information about the application. */

#ifndef ABOUT_WINDOW_VIEW_H
#define ABOUT_WINDOW_VIEW_H

#include <QDialog>

namespace Ui {
  class AboutWindowView;
}

class AboutWindowView : public QDialog
{
  Q_OBJECT

public:
  explicit AboutWindowView(QWidget *parent = 0);
  ~AboutWindowView();

public slots:
  void show_about_slideshow();
  void show_about_qt();
private slots:
  void on_pushButton_clicked();

private:
  Ui::AboutWindowView *ui;
};

#endif // ABOUT_WINDOW_VIEW_H
