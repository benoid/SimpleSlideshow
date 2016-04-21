#ifndef TESTCLASSMAIN_H
#define TESTCLASSMAIN_H

#include <QObject>
#include "slide_tests.h"
#include "slide_directory_tests.h"
#include "slide_queue_tests.h"

class TestClassMain : public QObject
{
  Q_OBJECT
public:
  explicit TestClassMain(QObject *parent = 0);

signals:

public slots:
  void run()
  {
  qDebug() << DEBUG_CONSOLE_DEFAULT_COLOR <<
              "\n************************************************************\n";\
  RUN_TEST_SUITE(SlideTests);
  RUN_TEST_SUITE(SlideDirectoryTests);
  RUN_TEST_SUITE(SlideQueueTests);
  qDebug() << "\n************************************************************\n";\


  qDebug () << DEBUG_CONSOLE_DEFAULT_COLOR <<
               "Note: if you are using qt-creator and all of the tests have failed, "
               "make sure the build directory is located at the root of the project tree.  "
               "Otherwise, the tests will not be able to find the required image files.";

  }
};

#endif // TESTCLASSMAIN_H
