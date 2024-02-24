#ifndef __TEST_ASM_HPP__
#define __TEST_ASM_HPP__

#include <vector>
#include <sys/types.h>
#include <string>

class TestAsm {
public:
  TestAsm();
  ~TestAsm();

  void test_strlen();
  static void print_setup();

private:
  std::vector<bool> tests_;

  static void print_test_header(const std::string&);
  static void print_test_case(int, const std::string&);
  static void print_test_result(bool);
  static void print_result(int, int);
};

#endif
