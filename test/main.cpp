#include "TestAsm.hpp"
#include <cstdlib>

int main()
{
  TestAsm::print_setup();
  
  TestAsm test_class;

  test_class.test_strlen();
  test_class.test_strcpy();
  return EXIT_SUCCESS;
}

