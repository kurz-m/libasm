#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

#include "TestAsm.hpp"
#include "libasm.h"
#include "colors.h"

#define IS_EQUAL(a, b) (a == b)

TestAsm::TestAsm() : tests_() {}

TestAsm::~TestAsm() {}

#define __verbose__

void TestAsm::test_strlen()
{
  print_test_header("FT_STRLEN");

  size_t own = 0;
  size_t ref = 0;
  std::vector<bool> check;

  const char* basic_stack = "Testing a basic string on the stack";

#ifdef __verbose__
  print_test_case(1, "String on the stack");
#endif

  own = ft_strlen(basic_stack);
  ref = std::strlen(basic_stack);
  check.push_back(IS_EQUAL(own, ref));
  print_test_result(IS_EQUAL(own, ref));

#ifdef __verbose__
  print_test_case(2, "String read from a file");
#endif

  std::ifstream file("dummy_file.txt");

  if (file.is_open()) {
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    own = ft_strlen(content.c_str());
    ref = content.length();
    check.push_back(IS_EQUAL(own, ref));
    print_test_result(IS_EQUAL(own, ref));
    file.close();
  }
  else {
    std::cerr << RED << "Could not open file for testing\n" << RESET;
  }

#ifdef __verbose__
  print_test_case(3, "String on the heap");
#endif

  std::string* ptr = new std::string("Classic Hello, World!");

  own = ft_strlen(ptr->c_str());
  ref = ptr->length();
  check.push_back(IS_EQUAL(own, ref));
  print_test_result(IS_EQUAL(own, ref));

  delete ptr;

#ifdef __verbose__
  print_test_case(4, "String literal");
#endif

  own = ft_strlen("Hello, World!");
  ref = std::strlen("Hello, World!");
  check.push_back(IS_EQUAL(own, ref));
  print_test_result(IS_EQUAL(own, ref));

#ifdef __verbose__
  print_test_case(5, "Empty string");
#endif

  own = ft_strlen("");
  ref = std::strlen("");
  check.push_back(IS_EQUAL(own, ref));
  print_test_result(IS_EQUAL(own, ref));

  // Counting successful tests
  int trues = std::count(check.begin(), check.end(), true);
  print_result(trues, check.size());
}

void TestAsm::print_setup()
{
  std::cout << BOLD << MAGENTA << "\n" << std::left << std::setw(40)
            << "TESTNAME" << std::right << std::setw(4) << "COMP\n"
            << RESET;
}

/**
 * @brief Small helper function to print which test
 * suite currently is being performed.
 * 
 * @param test String for being displayed.
 */
inline void TestAsm::print_test_header(const std::string& test)
{
  std::cout << YELLOW << "\n" + test + "\n" << RESET;
}

/**
 * @brief Prints the current test being carried out.
 * 
 * @param nb Test within the test suite.
 * @param test Description of the test case.
 */
inline void TestAsm::print_test_case(int nb, const std::string& test)
{
  std::string out = std::to_string(nb) + ". " + test;
  std::cout << std::left << std::setw(40) << out;
}

/**
 * @brief Print result from a single test.
 * 
 * @param result Bool given from the IS_EQUAL macro.
 */
inline void TestAsm::print_test_result(bool result)
{
  if (result) {
    std::cout << GREEN << "[OK]\n" << RESET;
  }
  else {
    std::cout << RED << "[KO]\n" << RESET;
  }
}

/**
 * @brief Prints how many test cases were successful.
 * 
 * @param trues How many trues are in the vector.
 * @param total Total number of tests carried out.
 */
inline void TestAsm::print_result(int trues, int total)
{
  std::cout << GREEN << "RESULT: " << trues << "/" << total
            << " tests were successful.\n" << RESET;
}