#include "TestAsm.hpp"
#include <cstdlib>

int main()
{
  TestAsm::print_setup();
  
  TestAsm test_class;

  test_class.test_strlen();
  return EXIT_SUCCESS;
}

