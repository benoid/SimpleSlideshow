# SimpleSlideshow
A Qt-based application that creates a slideshow and updates in real time 
based on files present in selected folders.  The goal is ease of use
and minimal user interaction, so the user can add and remove slides quickly
without needing to halt the slideshow.  

Disclaimer: This is a pre-release version of the application.  The developer
            The developer is not liable for any damages caused by the use
            or misuse of the application.  Some features may have bugs.
            See TODO.md for an idea of what still needs to be done.

# Features
- Supports both image and video slides
- Settings panel for easy access to configuration
- Configurable slide display timers
- Ability to sort and randomize slide queue 
- Select custom location from which to play slides
- Ability to display and configure informational 
  and marketing slides at regular intervals
- Ability to toggle inclusion of sub-folders of slides
  without removing them from local storage

# To compile
- Check Dependencies - see dependencies_list.md for more info
- run qmake on src/SimpleSlideshow.pro
 
# To Use
- Run the application. On startup it will create a profile folder 
  called SimpleSlideshow.  Within the profile folder will be a config file 
  and a folder called slide_directory.  The application wil look inside 
  slide_directory for any subdirectories, and automatically play slides from the 
  subdirectories. This allows users to organize slides into campaigns which can be 
  turned on and off easily without needing to add and remove files.
- Note: The application does NOT display slides from the root of slide_directory.  
  This is on my todo list to fix.  

# Supported Formats

Image
- jpeg
- gif
- bmp
- png
- pbm
- pgm
- ppm
- xbm

Video
- ogv
- avi
- mov
- mpg
- mp4
- flv
- wmv

Slide Format Note: The codecs to display these files are not 
bundled with the app.  They must be installed separately. 
libvorbis and gstreamer-plugins-good will cover most
of the open source formats, and qt5-image-format-plugins 
is sufficient for the image formats.  

