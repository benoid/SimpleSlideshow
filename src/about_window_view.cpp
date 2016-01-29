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
    along with SimpleSlideshow.  If not, see <http://www.gnu.org/licenses/>.*/

/* about_window_view.cpp

   Author: David Benoit
   Purpose: Implementation of AboutWindowView class */

#include "about_window_view.h"
#include "ui_about_window_view.h"

AboutWindowView::AboutWindowView(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AboutWindowView)
{
  ui->setupUi(this);
  this->setWindowTitle("About");
}

AboutWindowView::~AboutWindowView()
{
  delete ui;
}

void AboutWindowView::show_about_slideshow()
{
  ui->stackedWidget->setCurrentIndex(0);
  this->show();
}

void AboutWindowView::show_about_qt()
{
  ui->stackedWidget->setCurrentIndex(1);
  this->show();
}

void AboutWindowView::on_pushButton_clicked()
{
  this->close();
}
