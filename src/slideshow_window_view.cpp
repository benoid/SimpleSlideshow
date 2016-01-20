/* slideshow_window_view.cpp
 *
 * Author: David Benoit
 * Purpose: Implementation of the SlideshowWindowView class
 */

#include "slideshow_window_view.h"

SlideshowWindowView::SlideshowWindowView(QWidget *parent)
  : QMainWindow(parent)
{
  // Set Window Title
  this->setWindowTitle("Simple Slideshow");


  stacked_widget_ = new QStackedWidget;
  this->setCentralWidget(stacked_widget_);

  // Create and configure a QScrollArea to be the main
  // widget of the window
  scroll_area_widget_ = new QScrollArea;
  scroll_area_widget_->setStyleSheet("background-color: black; color: white");
  scroll_area_widget_->setAutoFillBackground(true);
  scroll_area_widget_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scroll_area_widget_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scroll_area_widget_->setWidgetResizable(true);

  stacked_widget_->addWidget(scroll_area_widget_);
  stacked_widget_->setCurrentWidget(scroll_area_widget_);

  // Create and configure QLabel to display images
  image_display_label_ = new QLabel;
  image_display_label_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  image_display_label_->setScaledContents(false);
  image_display_label_->setPixmap(QPixmap());
  image_display_label_->adjustSize();
  image_display_label_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

  // Add image_display_label to scroll_area_widget
  scroll_area_widget_->setWidget(image_display_label_);

  // Create Video Player
  media_player_ = new QMediaPlayer();
  video_widget_ = new QVideoWidget();
  media_playlist_ = new QMediaPlaylist();
  media_player_->setPlaylist(media_playlist_);
  media_player_->setVideoOutput(video_widget_);
  stacked_widget_->addWidget(video_widget_);
  connect(media_player_, SIGNAL(stateChanged(QMediaPlayer::State)),
          this, SLOT(hide_video_player()));


  // Create a default Right-Click context menu to house
  // access user interface features
  context_menu_ = new QMenu(tr("&Context Menu"));
  setContextMenuPolicy(Qt::CustomContextMenu);

  // Set up menu actions
  show_settings_view_action_= new QAction("Settings", this);
  quit_application_action_= new QAction("Quit", this);

  // Add actions to menu
  context_menu_->addAction(show_settings_view_action_);
  context_menu_->addAction(quit_application_action_);

  // Connect context menu action SIGNALS to SLOTS
  connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(show_context_menu(const QPoint &)));
  connect(quit_application_action_, SIGNAL(triggered(bool)), this, SLOT(quit_application()));
  connect(show_settings_view_action_, SIGNAL(triggered(bool)), this, SLOT(show_settings_view()));



}

SlideshowWindowView::~SlideshowWindowView()
{
  stacked_widget_->deleteLater();
  scroll_area_widget_->deleteLater();
  image_display_label_->deleteLater();
  media_player_->deleteLater();
  media_playlist_->deleteLater();
  video_widget_->deleteLater();
  context_menu_->deleteLater();
  show_settings_view_action_->deleteLater();
  quit_application_action_->deleteLater();

}

int SlideshowWindowView::display_image(QString image)
{

  // Check if the image exists and is valid
  if (QFile(image).exists() && !QPixmap(image).isNull())
    {
      // Display image
      image_display_label_->setPixmap(QPixmap(image).scaled(this->size(),
                       Qt::KeepAspectRatio, Qt::SmoothTransformation));

      // image display was successful, return 0
      return 0;
    }
  else
    {
      // image does not exist or is not supported format
      // return 0
      qWarning() << "Could not display image";
      return 1;
    }
}

void SlideshowWindowView::display_video(QString video)
{
  // Resize the video widget to fill the window
  video_widget_->resize(this->size());


  media_playlist_->addMedia(QUrl::fromLocalFile(video));
  media_playlist_->setCurrentIndex(media_playlist_->mediaCount() -1);

  //qWarning() << QFile().exists(media_playlist_->currentMedia().canonicalUrl().path());
  stacked_widget_->setCurrentWidget(video_widget_);
  media_player_->play();
  qWarning () << media_player_->state();

}

void SlideshowWindowView::hide_video_player()
{
  if (media_player_->state() == QMediaPlayer::StoppedState)
    {
      stacked_widget_->setCurrentWidget(scroll_area_widget_);
      emit video_finished_playing();
    }
}

void SlideshowWindowView::show_context_menu(const QPoint &pos)
{
  // check if context_menu_ is a null pointer
  if (context_menu_ != 0)
    {
      // show context menu
      context_menu_->exec(mapToGlobal(pos));
    }
}

void SlideshowWindowView::show_settings_view()
{
  emit settings_option_clicked();
}

void SlideshowWindowView::display_no_images_error()
{
   image_display_label_->setText("No images to display");
}
