#ifndef TESTSUITEMACROS_H
#define TESTSUITEMACROS_H

#include <QDebug>
#include <QString>
#include <QList>
#include <QStringList>

#include "../src/lib/ansi_colors.h"

#define STATUS bool
#define SUCCESS true
#define FAILURE false

#define ADD_TEST_METHOD(T,M) this->add_test(&T::M);
#define SET_CURRENT_TEST_NAME(N) this->set_current_test_name(N);
#define WARN_ERROR(E) this->append_error_list(E);
#define RUN_TEST_SUITE(T) T().run_all_tests();



// Use this macro at the top of a class derived from SimpleTestSuite
// to create a default test suite.  Create all tests as member functions
// in the derived class, and, in the class constructor, add the methods
// to the list_of_test_functions_(a list of function pointers) using
// the add_test(bool (T::*test_fn)()) method from the macro.
#define TEST_SUITE_CLASS(T) \
 private: \
  QString current_test_name_;\
  QStringList error_list_;\
  QList<bool (T::*)()> list_of_test_functions_; \
  \
  void add_test(bool (T::*test_fn)())\
    {\
      list_of_test_functions_.push_back(test_fn);\
    }\
  \
  int num_tests()\
    {\
      return list_of_test_functions_.size();\
    }\
  \
  bool run_test(int test_index)\
    {\
      return (this->*list_of_test_functions_.at(test_index))();\
    }\
  \
  QString suite_name()\
    {\
      return #T;\
    }\
  void set_current_test_name(QString test_name)\
  {\
    current_test_name_ = test_name;\
  }\
  void append_error_list(QString err)\
  {\
    error_list_.push_back(err);\
  }\
  public:\
    void run_all_tests()\
    {\
      int test_index, tests_passed = 0, tests_failed = 0;\
      qWarning() << DEBUG_CONSOLE_DEFAULT_COLOR <<\
                   "\nRunning Test Suite: " << suite_name() << "\n";\
      for (test_index = 0; test_index < num_tests(); ++test_index)\
        {\
          error_list_.clear();\
          current_test_name_ = "UNKNOWN TEST: Please use this->set_current_test_name"\
                               "(QString test_name) inside of each test function to "\
                               "specify the name of the test.";\
          if (run_test(test_index) == SUCCESS)\
            {\
              ++tests_passed;\
              qWarning() << DEBUG_CONSOLE_SUCCESS_COLOR <<\
                           "\tTEST PASSED: " <<\
                           DEBUG_CONSOLE_DEFAULT_COLOR <<\
                           current_test_name_ << "\n";\
            }\
          else\
            {\
              ++tests_failed;\
              qWarning() << DEBUG_CONSOLE_FAILURE_COLOR <<\
                           "\tTEST FAILED: " <<\
                           DEBUG_CONSOLE_DEFAULT_COLOR <<\
                           current_test_name_ <<\
                           DEBUG_CONSOLE_FAILURE_COLOR <<\
                           "With errors: ";\
              foreach (const QString &str, error_list_)\
                {\
                  qWarning() << DEBUG_CONSOLE_DEFAULT_COLOR <<\
                               "\t  " << str;\
                }\
              qWarning() << DEBUG_CONSOLE_DEFAULT_COLOR;\
            }\
        }\
      qWarning() << "Total Passed: " << tests_passed << "/"  << num_tests();\
      qWarning() << "Total Failed: " << tests_failed << "/"  << num_tests();\
    }\


#endif // TESTSUITEMACROS_H
