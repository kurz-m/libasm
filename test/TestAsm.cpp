#include <iostream>
#include <algorithm>
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
  print_test_header("TEST ft_strlen");

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


  // Counting successful tests
  int trues = std::count(check.begin(), check.end(), true);
  print_result(trues, check.size());
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
  std::cout << nb << ". " + test + "\t";
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
            << " tests were successful.\n";
}