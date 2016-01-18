/* slideshow_controller.h
 * 
 * Author: David Benoit
 * Purpose: Driver class for the slideshow
 *          creates and manages a SlideshowDataModel 
 *          object, SlideshowWindowView object,
 *          and SettingsWindowView object. Sends data from
 *          config file to SlideshowDataModel.  Is responsible for
 *          starting the slideshow.
 *          
 *           
 */

#ifndef SLIDESHOWCONTROLLER_H
#define SLIDESHOWCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QMenu>
#include <QDesktopServices>
#include <QTextStream>
#include <QDir>
#include <QDirIterator>
#include "queue_sort_order.h"
#include "slideshow_window_view.h"
#include "slideshow_data_model.h"
#include "settings_window_view.h"

class SlideshowController : public QObject
{
  Q_OBJECT
public:
  explicit SlideshowController(QObject *parent = 0);
  void begin_slideshow();

signals:

public slots:
/*** Slideshow SLOTs ***/

  // Display the next slide in the slide queue
  void show_next_slide();

  // Tell the slideshow_queue object that
  // The next image should be a marketing slide
  void queue_marketing_slide();

/*** Context menu SLOTs ***/
  // Show context menu
/*** Settings GUI SLOTs ***/

  // Display the settings gui to the screen
  void show_settings_view();

  // Import settings from gui, save them to
  // to the config file, and close the gui
  void gui_ok_button_pressed();

  // Close the gui without saving changes
  void gui_cancel_button_pressed();

  // Import settings from gui, save them to
  // to the config file, and close the gui
  void gui_apply_button_pressed();

private:
  SlideshowDataModel * slideshow_data_model_;
  SlideshowWindowView *slideshow_window_view_;
  SettingsWindowView * settings_window_view_;

  /*** Context menu and corresonding actions ***/
    // Right-click context menu
    QMenu * context_menu_;



    // Opens settings window to folder management tab
    QAction * show_directories_view_action_;

    // Quits the application
    QAction * quit_application_action_;

/*** Slideshow Timers ***/
  // Slide is updated upon timeout
  QTimer main_slide_timer_;

  // Marketing slides play upon timeout
  QTimer marketing_slide_timer_;

/*** Private function members ***/
  void set_all_settings_to_default();
  void ensure_folder_structure();
  void save_config_file(QString file_path);
  void parse_config_file(QString file_path);

  void export_settings_to_gui();
  void import_settings_from_gui();

  // notifies user of an error with the config fils
  void warn_config_error(QString key, QString value_str);

  // Checks main slide folder,
  // adds new slides,
  // removes nonexistant slides
  void refresh_slide_queue(); // This has an empty definition.
                              // TODO: Check for references and
                              // remove if unused

  void refresh_directory_list();
  void build_slide_queue();

};

#endif // SLIDESHOWCONTROLLER_H
