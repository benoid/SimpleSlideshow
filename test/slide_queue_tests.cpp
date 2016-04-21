#include "slide_queue_tests.h"
#include <QThread>


SlideQueueTests::SlideQueueTests()
{
  ADD_TEST_METHOD(SlideQueueTests, test_add_slide_directory);
  ADD_TEST_METHOD(SlideQueueTests, test_contains_dir);
  ADD_TEST_METHOD(SlideQueueTests, test_remove_dir);
  ADD_TEST_METHOD(SlideQueueTests, test_dir_list);
  ADD_TEST_METHOD(SlideQueueTests, test_size);
  ADD_TEST_METHOD(SlideQueueTests, test_contains_slide);

  // Functionality for this test is unfinished
  //ADD_TEST_METHOD(SlideQueueTests, test_service);
}

bool SlideQueueTests::test_add_slide_directory()
{
  SET_CURRENT_TEST_NAME("test_add_slide_directory")
      SlideQueue sq;
  sq.add_slide_directory("../test_slides/CC0_images0");
  sq.add_slide_directory("../test_slides/CC0_images1");
  sq.add_slide_directory("../test_slides/CC0_images2");

  if (sq.num_dirs() != 3)
    {
      WARN_ERROR("could not insert a slide directory");
      return FAILURE;
    }
  return SUCCESS;
}

bool SlideQueueTests::test_contains_dir()
{
  SET_CURRENT_TEST_NAME("test_contains_dir")
      SlideQueue sq;
  sq.add_slide_directory("../test_slides/CC0_images0");
  sq.add_slide_directory("../test_slides/CC0_images1");
  sq.add_slide_directory("../test_slides/CC0_images2");

  STATUS status = true;
  if (!sq.contains_dir("../test_slides/CC0_images0"))
    {
      WARN_ERROR("SlideQueue().contains() returns false on true condition");
      status = FAILURE;
    }
  if (sq.contains_dir("../tests/CC0_images3"))
    {
      WARN_ERROR("SlideQueue().contains() returns true on false condition");
      status = FAILURE;
    }
  return status;
}

bool SlideQueueTests::test_remove_dir()
{
  SET_CURRENT_TEST_NAME("test_remove_dir")
      SlideQueue sq;
  sq.add_slide_directory("../test_slides/CC0_images0");
  sq.add_slide_directory("../test_slides/CC0_images1");
  sq.add_slide_directory("../test_slides/CC0_images2");

  sq.remove_slide_directory("../test_slides/CC0_images2");
  if (sq.num_dirs() != 2)
    {
      WARN_ERROR("could not remove a slide directory");
      return FAILURE;
    }
  sq.remove_slide_directory("../test_slides/CC0_images1");
  if (sq.num_dirs() != 1)
    {
      WARN_ERROR("could not remove a slide directory");
      return FAILURE;
    }
  sq.remove_slide_directory("../test_slides/CC0_images0");
  if (sq.num_dirs() != 0)
    {
      WARN_ERROR("could not remove a slide directory");
      return FAILURE;
    }
  sq.remove_slide_directory("../test_slides/CC0_images0");
  if (sq.num_dirs() != 0)
    {
      WARN_ERROR("could not remove nonexistant slide from empty map");
      return FAILURE;
    }
  return SUCCESS;
}

bool SlideQueueTests::test_dir_list()
{
  SET_CURRENT_TEST_NAME("test_dir_list");
  SlideQueue sq;
  STATUS status = true;
  if (sq.dir_list().size() != 0)
    {
      WARN_ERROR("SlideQueue::dir_list() failed on empty list");
      status = FAILURE;
    }
  sq.add_slide_directory("../test_slides/CC0_images0");
  sq.add_slide_directory("../test_slides/CC0_images1");
  sq.add_slide_directory("../test_slides/CC0_images2");

  sq.add_slide_directory("../test_slides/CC0_images-info");


  if (sq.dir_list().size() != 4)
    {
      WARN_ERROR("SlideQueue::dir_list() failed to build a QStringList of all dirs");
      status = FAILURE;
    }
  return status;
}

bool SlideQueueTests::test_size()
{
  SET_CURRENT_TEST_NAME("test_size");
  SlideQueue sq;
  STATUS status = true;
  if (sq.size() != 0)
    {
      WARN_ERROR("SlideQueue::size() failed on empty list");
      status = FAILURE;
    }
  sq.add_slide_directory("../test_slides/CC0_images0");
  if (sq.size() != 0)
    {
      WARN_ERROR("SlideQueue::size() failed on empty list after dir added");
      status = FAILURE;
    }
  sq.refresh_all_dirs();
  if (sq.size() != 9)
    {
      WARN_ERROR("SlideQueue::size() failed after initial refresh");
      status = FAILURE;
    }
  return status;
}

bool SlideQueueTests::test_contains_slide()
{
  SET_CURRENT_TEST_NAME("test_contains_slide");
  SlideQueue sq;
  STATUS status = true;
  sq.add_slide_directory("../test_slides/CC0_images0");
  sq.add_slide_directory("../test_slides/CC0_images1");
  sq.add_slide_directory("../test_slides/CC0_images2");

  sq.add_slide_directory("../test_slides/CC0_images-info");
  sq.refresh_all_dirs();
  if (!sq.contains_slide(Slide("../test_slides/CC0_images0/forest.jpg")))
    {
      WARN_ERROR("SlideQueue::contains_slide() returns false when slide exists");
      status = FAILURE;
    }
  return status;
}

bool SlideQueueTests::test_service()
{
  SET_CURRENT_TEST_NAME("test_service");
  SlideQueue sq;
  sq.add_slide_directory("../test_slides/CC0_images0");
  sq.add_slide_directory("../test_slides/CC0_images1");
  sq.add_slide_directory("../test_slides/CC0_images2");

  sq.add_slide_directory("../test_slides/CC0_images-info");

  for (;;)//int i = 0; i < sq.size() * 2; ++i)
    {
      qWarning () << sq.service().file_path();
      QThread::sleep(5);
    }
  return FAILURE;

}
