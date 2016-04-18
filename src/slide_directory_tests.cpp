#include "slide_directory_tests.h"


STATUS SlideDirectoryTests::test_create_slide_group()
{
  SET_CURRENT_TEST_NAME("test_create_slide_name");
  QString dir_path = "SimpleSlideshow2/test/images";
  SlideDirectory sg("../" + dir_path);
  if (sg.dir_path().contains(dir_path))
    {
      return SUCCESS;
    }
  WARN_ERROR("SlideDirectory.dir_path() does not contain dir_path")
  return FAILURE;
}

bool SlideDirectoryTests::test_is_informational()
{
  SET_CURRENT_TEST_NAME("test_is_informational")
  SlideDirectory sg_true("hello-info"), sg_false("hello");
  STATUS status = true;
  if (!sg_true.is_informational())
    {
      WARN_ERROR("SlideDirectory.is_informational() returns false on true condition");
      status = false;
    }
  if (sg_false.is_informational())
    {
      WARN_ERROR("SlideDirectory.is_informational() returns true on false condition");
      status = false;
    }
  return status;
}

bool SlideDirectoryTests::test_build_from_local_dir()
{
  SET_CURRENT_TEST_NAME("test_build_from_local_dir");
  SlideDirectory sg("../SimpleSlideshow2/test/images");
  sg.build_from_local_dir();
  if (sg.size() <= 0)
  {
    WARN_ERROR("could not build from local directory")
        return FAILURE;
  }
  return SUCCESS;
}

bool SlideDirectoryTests::test_refresh_contents()
{
  SET_CURRENT_TEST_NAME("test_refresh_contents");
  SlideDirectory sg1("../SimpleSlideshow2/test/images");
  SlideDirectory sg2("../SimpleSlideshow2/test/images");
  STATUS status = SUCCESS;
  sg1.build_from_local_dir();
  if (sg1.qList().size() != sg2.refresh_contents().size() || sg2.qList().isEmpty())
  {
    WARN_ERROR("SlideDirectory().refresh failed");
    status = FAILURE;
  }
  sg1.insert(Slide("hello.jpg"));
  if (sg1.size() != 5)
    {
      WARN_ERROR("insert hello.jpg failed")
      status = FAILURE;
    }
  sg1.refresh_contents();
  if (sg1.size() != 4)
    {
      WARN_ERROR("did not purge nonexistant files")
          status = FAILURE;
    }

  return status;
}

bool SlideDirectoryTests::test_qList()
{
  SET_CURRENT_TEST_NAME("test_qList");
  SlideDirectory sg("../SimpleSlideshow2/test/images");
  sg.build_from_local_dir();
  STATUS status = SUCCESS;
  if (sg.qList().size() < 4)
  {
    WARN_ERROR("SlideDirectory().qList() failed");
    status =  FAILURE;
  }
  if (sg.qList().size() != sg.size())
  {
    WARN_ERROR("SlideDirectory::qList().size() != SlideDirectory::size()");
    status =  FAILURE;
  }
  return status;
}

bool SlideDirectoryTests::test_contains()
{
  SET_CURRENT_TEST_NAME("test_contains");
  SlideDirectory sg("../SimpleSlideshow2/test/images");
  sg.build_from_local_dir();
  QList<Slide> l = sg.qList();
  if (!sg.contains(Slide("../SimpleSlideshow2/test/images/forest.jpg")))
  {
    WARN_ERROR("SlideDirectory::contains() failed");
    return FAILURE;
  }
  return SUCCESS;
}

bool SlideDirectoryTests::test_purge_nonexistant_entries()
{
  SET_CURRENT_TEST_NAME("test_purge_nonexistant_entries");
  SlideDirectory sg("../SimpleSlideshow2/test/images");
  sg.build_from_local_dir();
  STATUS status = SUCCESS;
  if (sg.size() != 4)
  {
    WARN_ERROR("SlideDirectory::size() failed");
    status =  FAILURE;
  }
  sg.insert(Slide("hello.jpg"));
  if (sg.size() != 5)
  {
    WARN_ERROR("SlideDirectory::size() failed");
    status =  FAILURE;
  }
  sg.purge_nonexistant_entries();
  if (sg.size() != 4)
  {
    WARN_ERROR("SlideDirectory::purge_nonexistant_entries failed");
    status =  FAILURE;
  }
  return status;
}

SlideDirectoryTests::SlideDirectoryTests()
{
  ADD_TEST_METHOD(SlideDirectoryTests, test_create_slide_group);
  ADD_TEST_METHOD(SlideDirectoryTests, test_is_informational);
  ADD_TEST_METHOD(SlideDirectoryTests, test_build_from_local_dir);
  ADD_TEST_METHOD(SlideDirectoryTests, test_qList);
  ADD_TEST_METHOD(SlideDirectoryTests, test_refresh_contents);
  ADD_TEST_METHOD(SlideDirectoryTests, test_contains);
  ADD_TEST_METHOD(SlideDirectoryTests, test_purge_nonexistant_entries);
}
