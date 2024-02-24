#ifndef __TEST_ASM_HPP__
#define __TEST_ASM_HPP__

#include <vector>
#include <sys/types.h>

class TestAsm {
public:
  TestAsm();
  ~TestAsm();

  bool test_strlen();

private:
  std::vector<bool> tests_;
};

#endif
