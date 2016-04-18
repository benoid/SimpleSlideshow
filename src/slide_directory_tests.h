#ifndef SLIDEDIRECTORYTESTS_H
#define SLIDEDIRECTORYTESTS_H
#include "test_suite_macros.h"
#include "slide_directory.h"
#include <QDebug>

class SlideDirectoryTests
{
  TEST_SUITE_CLASS(SlideDirectoryTests)
public:
  SlideDirectoryTests();

  STATUS test_create_slide_group();
  STATUS test_is_informational();
  STATUS test_build_from_local_dir();
  STATUS test_refresh_contents();
  STATUS test_qList();
  STATUS test_contains();
  STATUS test_purge_nonexistant_entries();


};

#endif // SLIDEDIRECTORYTESTS_H
