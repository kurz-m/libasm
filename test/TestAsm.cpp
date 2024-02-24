#include <iostream>
#include <cstdlib>

#include "TestAsm.hpp"
#include "libasm.h"

#define IS_EQUAL(a, b) (a == b)

TestAsm::TestAsm() : tests_() {}

TestAsm::~TestAsm() {}

bool TestAsm::test_strlen()
{
  size_t own = 0;
  size_t ref = 0;
  bool  check = false;

  // First test
  std::string basic_stack("Just here for checking something");

#ifdef __verbose__
  std::cout << "Testing a basic string on the stack\n";
#endif

  own = ft_strlen(basic_stack.c_str());
  ref = basic_stack.length();
  check = IS_EQUAL(own, ref);

  if (check == false) {
    return false;
  }

  return true;
}
