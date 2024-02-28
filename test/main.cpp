#include "TestAsm.hpp"
#include <cstdlib>

int main()
{
  TestAsm::print_setup();
  
  TestAsm test_class;

  test_class.test_strlen();
  test_class.test_strcpy();
  test_class.test_strcmp();

  return EXIT_SUCCESS;
}

