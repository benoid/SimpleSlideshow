#ifndef SLIDETESTS_H
#define SLIDETESTS_H
#include "./test_suite_macros.h"
#include "../src/lib/slide.h"
#include <QFile>

class SlideTests
{
  TEST_SUITE_CLASS(SlideTests)
public:
  SlideTests();
  STATUS test_create_slide();
  STATUS test_process_slide_type();
  STATUS test_slide_exists();
};

#endif // SLIDETESTS_H

