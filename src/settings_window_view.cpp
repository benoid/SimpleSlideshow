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

/* settings_window_view.cpp

   Author: David Benoit
   Purpose: Implementation of the SettingsWindowView class. */

#include "settings_window_view.h"
#include "ui_settings_window_view.h"
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFileDialog>


SettingsWindowView::SettingsWindowView(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SettingsWindowView)
{
  ui->setupUi(this);
  this->setWindowTitle("Application Settings");
  this->setFixedSize(724, 438);
  this->setWindowFlags(Qt::WindowStaysOnTopHint);

  fullscreen_disabled_bool_ = 0;
  begin_on_marketing_slide_bool_ = 0;
  randomize_images_bool_ = 0;
  main_timer_interval_ = 0;
  marketing_timer_interval_ = 0;
  main_sort_order_ = (QueueSortOrder) 0;
  marketing_sort_order_ =(QueueSortOrder) 0;
  marketing_playback_option_ =(MarketingPlaybackOption) 0;


  // Set tabWidget to settings tab
  ui->tabWidget->setCurrentIndex(0);
  connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), ui->tableWidget, SLOT(sortByColumn(int)));

}

void SettingsWindowView::apply_settings()
{
  int temp;

  // Update config settings if valid
  temp =  ui->lineEdit->value();
  if (temp > 0)
    {
      main_timer_interval_ = temp * 1000;
    }
  temp =  ui->lineEdit_2->value();
  if (temp > 0)
    {
      marketing_timer_interval_ = temp * 1000;
    }
  temp =  ui->lineEdit_3->value();
  if (temp > 0)
    {
      indiv_info_interval_ = temp * 1000;
    }
  main_sort_order_ = (QueueSortOrder) ui->comboBox->currentIndex();
  marketing_sort_order_ = (QueueSortOrder) ui->comboBox_2->currentIndex();
  marketing_playback_option_ = (MarketingPlaybackOption) ui->checkBox_6->checkState();
  fullscreen_disabled_bool_ = ui->checkBox->isChecked();
  begin_on_marketing_slide_bool_ = ui->checkBox_5->isChecked();

  if (slide_folder_path() != ui->lineEdit_4->text())
    {
      slide_folder_path_ = ui->lineEdit_4->text();
      emit slide_folder_changed();
    }

  for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
      bool match_found = false;
      for (int j = 0; !match_found && j < slide_directory_list_.size(); ++j)
        {
          // Check for equal match
          if (ui->tableWidget->item(i,0)->text()
              == slide_directory_list_[j].name())
            {
              match_found = true;
              if (ui->tableWidget->item(i,2)->checkState())
                {
                  QDir(slide_directory_list_[j].full_path()).removeRecursively();
                }
              else if (!ui->tableWidget->item(i,1)->checkState())
                {
                  // File should be hidden
                  QDir().rename(slide_directory_list_[j].full_path(),
                                slide_folder_path_ + "/."
                                + slide_directory_list_[j].name());
                }
            }
          // Check for opposite match
          else if (slide_directory_list_[j].name().at(0) == '.')
            {
              if (slide_directory_list_[j].name().remove(0,1)
                  == ui->tableWidget->item(i,0)->text())
                {
                  match_found = true;
                  if (ui->tableWidget->item(i,2)->checkState())
                    {
                      //QDir(slide_directory_list_[j].full_path()).removeRecursively();
                    }
                  else if (ui->tableWidget->item(i,1)->checkState())
                    {
                      // File should be hidden
                      slide_directory_list_[j].set_dir_name(
                            ui->tableWidget->item(i,0)->text());
                      QDir().rename(slide_directory_list_[j].full_path(),
                                    slide_folder_path_ + "/"
                                    + slide_directory_list_[j].name());
                    }
                }
            }
        }
    }
}


SettingsWindowView::~SettingsWindowView()
{
  delete ui;
}

void SettingsWindowView::set_up_gui()
{

  // Clear contents of table
  ui->tableWidget->clearContents();
  while (ui->tableWidget->rowCount() > 0)
    {
      ui->tableWidget->removeRow(0);
    }
  // Set up table
  for (int i = 0; i < slide_directory_list_.size(); ++i)
    {
      // Column 1
      table_item = new QTableWidgetItem;
      table_item->setText(slide_directory_list_[i].name());
      table_item->setFlags(table_item->flags() ^ Qt::ItemIsEditable);
      ui->tableWidget->insertRow(0);
      ui->tableWidget->setItem(0, 0, table_item);

      // Column 2
      table_item = new QTableWidgetItem;
      if(ui->tableWidget->item(0,0)->text().at(0) == '.')
        {
          // Strip dot from hidden folder
          ui->tableWidget->item(0,0)->setText(
                ui->tableWidget->item(0,0)->text().remove(0,1));
          table_item->setCheckState(Qt::Unchecked);
        }
      else
        {
          table_item->setCheckState(Qt::Checked);
        }
      ui->tableWidget->setItem(0, 1, table_item);

      // Column 3
      table_item = new QTableWidgetItem;
      table_item->setCheckState(Qt::Unchecked);
      ui->tableWidget->setItem(0, 2, table_item);

    }
  ui->tableWidget->resizeColumnsToContents();

  ui->lineEdit->setValue(main_timer_interval_/1000.0);
  ui->lineEdit_2->setValue(marketing_timer_interval_/1000.0);
  ui->lineEdit_3->setValue(indiv_info_interval_/1000);
  ui->lineEdit_4->setText(slide_folder_path());

  ui->checkBox->setChecked(fullscreen_disabled_bool_);
  ui->checkBox_5->setChecked(begin_on_marketing_slide_bool_);
  ui->comboBox->setCurrentIndex((int)main_sort_order_);
  ui->comboBox_2->setCurrentIndex((int)marketing_sort_order_);
  ui->checkBox_6->setChecked((bool) marketing_playback_option_);
  ui->tableWidget->hideColumn(2);

  // Disable changing folder location
  // ui->lineEdit_4->setDisabled(true);
  // ui->pushButton_2->setDisabled(true);
}

void SettingsWindowView::set_focus_main_tab()
{
  ui->tabWidget->setCurrentIndex(0);
}

void SettingsWindowView::set_focus_folders_tab()
{
  ui->tabWidget->setCurrentIndex(1);
}

void SettingsWindowView::set_slide_folder_path(QString set_path)
{
  slide_folder_path_ = set_path;
}

void SettingsWindowView::set_main_timer_interval(int set_interval)
{
  main_timer_interval_ = set_interval;
}

void SettingsWindowView::set_marketing_timer_interval(int set_interval)
{
  marketing_timer_interval_ = set_interval;
}

void SettingsWindowView::set_fullscreen_disabled(bool set_disabled)
{
  fullscreen_disabled_bool_ = set_disabled;
}

void SettingsWindowView::set_begin_on_marketing_slide(bool set_enabled)
{
  begin_on_marketing_slide_bool_ = set_enabled;
}

void SettingsWindowView::set_randomize_images(bool set_enabled)
{

  randomize_images_bool_ = set_enabled;
}

void SettingsWindowView::set_slide_directory_list(QList<SlideDirectory> dir_list)
{
  slide_directory_list_ = dir_list;
}

void SettingsWindowView::set_marketing_order(QueueSortOrder option)
{
  marketing_sort_order_ = option;
}

void SettingsWindowView::set_main_order(QueueSortOrder option)
{
  main_sort_order_ = option;
}

void SettingsWindowView::set_marketing_option(MarketingPlaybackOption option)
{
  marketing_playback_option_ = option;
}

void SettingsWindowView::set_indiv_info_interval(int set)
{
  indiv_info_interval_ = set;
}

QueueSortOrder SettingsWindowView::main_order_option()
{
  return main_sort_order_;
}

QueueSortOrder SettingsWindowView::marketing_order_option()
{
  return marketing_sort_order_;
}

MarketingPlaybackOption SettingsWindowView::marketing_option()
{
  return marketing_playback_option_;
}

bool SettingsWindowView::begin_on_marketing_slide_bool()
{
  return begin_on_marketing_slide_bool_;
}

bool SettingsWindowView::randomize_images_bool()
{
  return randomize_images_bool_;
}

int SettingsWindowView::main_timer_interval()
{
  return main_timer_interval_;
}

int SettingsWindowView::marketing_timer_interval()
{
  return marketing_timer_interval_;
}

int SettingsWindowView::indiv_info_interval()
{
  return indiv_info_interval_;
}

bool SettingsWindowView::fullscreen_disabled()
{
  return fullscreen_disabled_bool_;
}

QString SettingsWindowView::slide_folder_path()
{
  return slide_folder_path_;
}

void SettingsWindowView::on_buttonBox_accepted()
{
  apply_settings();
  emit ok_button_pressed();
}

void SettingsWindowView::on_buttonBox_rejected()
{
  emit cancel_button_pressed();
}

// Update but don't close
void SettingsWindowView::on_pushButton_clicked()
{
  apply_settings();
  emit apply_button_pressed();
}

void SettingsWindowView::on_pushButton_2_clicked()
{
  QString temp = QFileDialog::getExistingDirectory(this, tr("Select Remote Image Folder"), QDir::homePath(), QFileDialog::ReadOnly | QFileDialog::ShowDirsOnly);
  if (temp != "")
    {
      ui->lineEdit_4->setText(temp);
    }
}
