#include "slide_tests.h"

SlideTests::SlideTests()
{
  ADD_TEST_METHOD(SlideTests, test_create_slide);
  ADD_TEST_METHOD(SlideTests, test_process_slide_type);
  ADD_TEST_METHOD(SlideTests, test_slide_exists);
}

STATUS SlideTests::test_create_slide()
{
  SET_CURRENT_TEST_NAME("test_create_slide")

  STATUS status = SUCCESS;
  Slide a("hello.jpg");
  Slide b("goodbye.ogv");
  Slide c;
  c.set_file_path("blah.txt");
  if (a.file_path() != "hello.jpg")
    {
      WARN_ERROR("Slide a != hello.jpg")
      status = FAILURE;
    }
  if (b.file_path() != "goodbye.ogv")
    {
      WARN_ERROR("Slide b != goodbye.ogv")
      status = FAILURE;
    }
  if (c.file_path() != "blah.txt")
    {
      WARN_ERROR("Slide c != blah.txt")
      status = FAILURE;
    }
  return status;
}

STATUS SlideTests::test_process_slide_type()
{
  SET_CURRENT_TEST_NAME("test_process_slide_type")

  STATUS status = SUCCESS;
  Slide a("hello.jpg");
  Slide b("goodbye.ogv");
  Slide c;
  c.set_file_path("blah.txt");
  if (a.slide_type() != IMAGE)
    {
      this->append_error_list("a.slide_type() != IMAGE");
      status = FAILURE;
    }
  if (b.slide_type() != VIDEO)
    {
      this->append_error_list("b.slide_type() != VIDEO");
      status = FAILURE;
    }
  if (c.slide_type() != INVALID_SLIDE)
    {
      this->append_error_list("c.slide_type() != INVALID_SLIDE");
      status = FAILURE;
    }
  return status;
}

bool SlideTests::test_slide_exists()
{
  SET_CURRENT_TEST_NAME("test_slide_exists");
  Slide s("SimpleSlideshow2");
  QFile slide_file(s.file_path());
  if (!slide_file.open(QFile::ReadOnly))
    {
      WARN_ERROR("could not open or create file");
      return FAILURE;
    }
  if (!s.exists())
    {
      append_error_list("Slide().exists() returns false when file exists");
      slide_file.close();
      return FAILURE;
    }
  else
    {
      slide_file.close();
      return SUCCESS;
    }

}


