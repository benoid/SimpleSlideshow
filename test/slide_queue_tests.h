#ifndef SLIDEQUEUETESTS_H
#define SLIDEQUEUETESTS_H
#include "test_suite_macros.h"
#include "../src/lib/slide_queue.h"

class SlideQueueTests
{
  TEST_SUITE_CLASS(SlideQueueTests)
public:
  SlideQueueTests();

  STATUS test_add_slide_directory();
  STATUS test_contains_dir();
  STATUS test_remove_dir();
  STATUS test_dir_list();
  STATUS test_size();
  STATUS test_contains_slide();
  STATUS test_service();
};

#endif // SLIDEQUEUETESTS_H
