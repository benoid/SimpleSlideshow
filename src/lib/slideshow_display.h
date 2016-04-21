#ifndef SLIDESHOW_DISPLAY_H
#define SLIDESHOW_DISPLAY_H

#include <QMainWindow>

class SlideshowDisplay : public QMainWindow
{
    Q_OBJECT

public:
    SlideshowDisplay(QWidget *parent = 0);
    ~SlideshowDisplay();
};

#endif // SLIDESHOW_DISPLAY_H
