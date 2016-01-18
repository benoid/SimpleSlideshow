#ifndef SETTINGSWINDOWVIEW_H
#define SETTINGSWINDOWVIEW_H

#include <QDialog>
#include <QString>
#include <QTableWidget>
#include <QList>
#include "queue_sort_order.h"
#include "slide_directory.h"

namespace Ui {
  class SettingsWindowView;
}

class SettingsWindowView : public QDialog
{
  Q_OBJECT
public:
  explicit SettingsWindowView(QWidget *parent = 0);
  ~SettingsWindowView();

  // Sets the values in the gui text field to the
  // Corresponding values of the classes private variables
  void set_up_gui();

  // Sets the tab widget's focus to the main tab
  void set_focus_main_tab();

  // Sets the tab widget's focus to the folders view tab
  void set_focus_folders_tab();

  // Mutators
  void set_slide_folder_path(QString set_path){
    slide_folder_path_ = set_path;}
  void set_main_timer_interval(int set_interval){
    main_timer_interval_ = set_interval;}
  void set_marketing_timer_interval(int set_interval){
    marketing_timer_interval_ = set_interval;}
  void set_fullscreen_disabled(bool set_disabled){
    fullscreen_disabled_bool_ = set_disabled;}
  void set_begin_on_marketing_slide(bool set_enabled){
    begin_on_marketing_slide_bool_ = set_enabled;}
  void set_randomize_images(bool set_enabled){
    randomize_images_bool_ = set_enabled;}
  void set_slide_directory_list(QList<SlideDirectory> dir_list);
  void set_marketing_order(QueueSortOrder option){
    marketing_sort_order_ = option;}
  void set_main_order(QueueSortOrder option){
    main_sort_order_ = option;}
  void set_marketing_option(MarketingPlaybackOption option){
    marketing_playback_option_ = option;}


  // Accessors
  QueueSortOrder main_order_option(){
    return main_sort_order_;}
  QueueSortOrder marketing_order_option(){
    return marketing_sort_order_;}
  MarketingPlaybackOption marketing_option(){
    return marketing_playback_option_;}
  bool begin_on_marketing_slide_bool(){
    return begin_on_marketing_slide_bool_;}
  bool randomize_images_bool(){return randomize_images_bool_;}
  int main_timer_interval(){return main_timer_interval_;}
  int marketing_timer_interval(){return marketing_timer_interval_;}
  bool fullscreen_disabled(){return fullscreen_disabled_bool_;}
  QString slide_folder_path(){return slide_folder_path_;}

signals:
  void ok_button_pressed();
  void cancel_button_pressed();
  void apply_button_pressed();

private:
  Ui::SettingsWindowView *ui;

  // Display stuff

  QString slide_folder_path_;
  QList<SlideDirectory> slide_directory_list_;

  QTableWidgetItem * table_item;
  bool fullscreen_disabled_bool_;
  bool begin_on_marketing_slide_bool_;
  bool randomize_images_bool_;
  int main_timer_interval_;
  int marketing_timer_interval_;

  QueueSortOrder main_sort_order_;
  QueueSortOrder marketing_sort_order_;
  MarketingPlaybackOption marketing_playback_option_;


  // Private methods
  void apply_settings();

private slots:
  void on_buttonBox_accepted();
  void on_buttonBox_rejected();
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
};

#endif // SETTINGSWINDOWVIEW_H
