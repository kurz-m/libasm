#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#include "TestAsm.hpp"
#include "colors.h"
#include "libasm.h"

/*****************************************************************************/
// MACROS and inline functions
template <typename T> static inline bool is_equal(T &a, T &b) { return a == b; }

template <typename T> static inline bool same_sign(T &a, T &b) {
  return (a >> 7) == (b >> 7);
}

// static inline bool equal_string(const char* a, const char* b) {
//   return std::strcmp(a, b) == 0 ? true : false;
// }

#define IS_EQUAL(a, b) (a == b)
#define SAME_SIGN(a, b) ((a >> 7) == (b >> 7))
#define EQUAL_STR(a, b) (std::strcmp(a, b) == 0 ? true : false)
#define RESET_BUF(str) (std::memset(str, 0, std::strlen(str)))
/*****************************************************************************/

TestAsm::TestAsm() : tests_() {}

TestAsm::~TestAsm() {}

#define __verbose__

/**
 * Function for testing ft_strlen.
 *
 * This function tests different cases for the ft_strlen function
 * written in x86 assembly.
 */
void TestAsm::test_strlen() {
  print_test_header("FT_STRLEN");

  size_t own = 0;
  size_t ref = 0;
  std::vector<bool> check;

  const char *basic_stack = "Testing a basic string on the stack";

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
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    own = ft_strlen(content.c_str());
    ref = content.length();
    check.push_back(IS_EQUAL(own, ref));
    print_test_result(IS_EQUAL(own, ref));
    file.close();
  } else {
    std::cerr << RED << "Could not open file for testing\n" << RESET;
  }

#ifdef __verbose__
  print_test_case(3, "String on the heap");
#endif

  std::string *ptr = new std::string("Classic Hello, World!");

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

/**
 * Function for testing ft_strcpy.
 *
 * This function tests different cases for the ft_strcpy function
 * written in x86 assembly.
 */
void TestAsm::test_strcpy() {
  print_test_header("FT_STRCPY");
  std::vector<bool> check;

#ifdef __verbose__
  print_test_case(1, "String literal in read-only memory");
#endif

  const char *test1_string = "Hello World!";
  char *own = new char[std::strlen(test1_string) + 1]();
  char *ref = new char[std::strlen(test1_string) + 1]();

  ft_strcpy(own, test1_string);
  std::strcpy(ref, test1_string);
  check.push_back(EQUAL_STR(own, ref));
  print_test_result(EQUAL_STR(own, ref));
  RESET_BUF(own);
  RESET_BUF(ref);

#ifdef __verbose__
  print_test_case(2, "Mutable char array");
#endif

  const char test2_string[] = "Hello World!";

  ft_strcpy(own, test2_string);
  std::strcpy(ref, test2_string);
  check.push_back(EQUAL_STR(own, ref));
  print_test_result(EQUAL_STR(own, ref));

  delete[] own;
  delete[] ref;

#ifdef __verbose__
  print_test_case(3, "String read from a file");
#endif

  std::ifstream file("dummy_file.txt");

  if (file.is_open()) {
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    own = new char[std::strlen(content.c_str()) + 1]();
    ref = new char[std::strlen(content.c_str()) + 1]();

    ft_strcpy(own, content.c_str());
    std::strcpy(ref, content.c_str());
    check.push_back(EQUAL_STR(own, ref));
    print_test_result(EQUAL_STR(own, ref));
    RESET_BUF(own);
    RESET_BUF(ref);
    delete[] own;
    delete[] ref;
    file.close();
  } else {
    std::cerr << RED << "Could not open file for testing\n" << RESET;
  }

#ifdef __verbose__
  print_test_case(4, "Empty string");
#endif

  own = new char[std::strlen("") + 1]();
  ref = new char[std::strlen("") + 1]();

  ft_strcpy(own, "");
  std::strcpy(ref, "");
  check.push_back(EQUAL_STR(own, ref));
  print_test_result(EQUAL_STR(own, ref));
  RESET_BUF(own);
  RESET_BUF(ref);
  delete[] own;
  delete[] ref;

#ifdef __verbose__
  print_test_case(5, "String on the heap");
#endif

  const char copy_str[] = "This is a string on the heap";

  char *copy = new char[std::strlen(copy_str) + 1]();
  for (size_t i = 0; i < std::strlen(copy_str); ++i) {
    copy[i] = copy_str[i];
  }
  own = new char[std::strlen(copy_str) + 1]();
  ref = new char[std::strlen(copy_str) + 1]();

  ft_strcpy(own, copy);
  std::strcpy(ref, copy);
  check.push_back(EQUAL_STR(own, ref));
  print_test_result(EQUAL_STR(own, ref));
  RESET_BUF(own);
  RESET_BUF(ref);
  delete[] own;
  delete[] ref;
  delete[] copy;

  // Counting successful tests
  int trues = std::count(check.begin(), check.end(), true);
  print_result(trues, check.size());
}

/**
 * Function for testing ft_strcmp.
 *
 * This function tests different cases for the ft_strcmp function
 * written in x86 assembly.
 */
void TestAsm::test_strcmp() {
  print_test_header("FT_STRCMP");
  std::vector<bool> check;

#ifdef __verbose__
  print_test_case(1, "Same string literal");
#endif

  const char *test1_string = "Hello World!";
  const char *test2_string = "Hello World!";
  int own = 0;
  int ref = 0;

  own = ft_strcmp(test1_string, test2_string);
  ref = std::strcmp(test1_string, test2_string);
  check.push_back(IS_EQUAL(own, ref));
  print_test_result(IS_EQUAL(own, ref));

#ifdef __verbose__
  print_test_case(2, "Same mutable char array");
#endif

  const char mut1[] = "Hello World!";
  const char mut2[] = "Hello World!";

  own = ft_strcmp(mut1, mut2);
  ref = std::strcmp(mut1, mut2);
  check.push_back(IS_EQUAL(own, ref));
  print_test_result(IS_EQUAL(own, ref));

#ifdef __verbose__
  print_test_case(3, "One empty string");
#endif

  const char empty[] = "";

  own = ft_strcmp(mut1, empty);
  ref = std::strcmp(mut1, empty);
  check.push_back(same_sign(own, ref));
  print_test_result(same_sign(own, ref));

#ifdef __verbose__
  print_test_case(4, "Two empty strings");
#endif

  own = ft_strcmp("", empty);
  ref = std::strcmp("", empty);
  check.push_back(IS_EQUAL(own, ref));
  print_test_result(IS_EQUAL(own, ref));

#ifdef __verbose__
  print_test_case(5, "String read from a file");
#endif

  std::ifstream file("dummy_file.txt");

  if (file.is_open()) {
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    std::string file1 = content.substr(0, 25);
    std::string file2 = content.substr(10, 22);

    own = strcmp(file1.c_str(), file2.c_str());
    ref = std::strcmp(file1.c_str(), file2.c_str());
    check.push_back(same_sign(own, ref));
    print_test_result(same_sign(own, ref));
    file.close();
  } else {
    std::cerr << RED << "Could not open file for testing\n" << RESET;
  }

#ifdef __verbose__
  print_test_case(6, "Negative return value");
#endif

  own = ft_strcmp("z", "A");
  ref = std::strcmp("z", "A");
  check.push_back(same_sign(own, ref));
  print_test_result(same_sign(own, ref));

#ifdef __verbose__
  print_test_case(7, "String on the heap");
#endif

  const char copy_str[] = "This is a string on the heap";

  char *copy = new char[std::strlen(copy_str) + 1]();
  for (size_t i = 0; i < std::strlen(copy_str); ++i) {
    copy[i] = copy_str[i];
  }

  own = ft_strcmp(copy_str, copy_str);
  ref = std::strcmp(copy_str, copy_str);
  check.push_back(is_equal(own, ref));
  print_test_result(is_equal(own, ref));
  delete[] copy;

  // Counting successful tests
  int trues = std::count(check.begin(), check.end(), true);
  print_result(trues, check.size());
}

#include <signal.h>

/**
 * Function for testing ft_write.
 *
 * This function tests different cases for the ft_write function
 * written in x86 assembly.
 */
void TestAsm::test_write() {
  signal(SIGPIPE, SIG_IGN);
  print_test_header("FT_WRITE");
  std::vector<bool> check;
  int own = 0;
  int ref = 0;

#ifdef __verbose__
  print_test_case(1, "String literal");
#endif

  int fd = open("test_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0) {
  } else {
    own = ft_write(fd, "hello\n", 6);
    ref = 6;
    check.push_back(is_equal(own, ref));
    print_test_result(is_equal(own, ref));
    std::remove("test_file.txt");
  }

  std::cout << "EFAULT: " << ft_write(1, NULL, 10) << std::endl;
  std::cout << "EBADF: " << ft_write(-1, "test\n", 5) << std::endl;
  int ronly = open("test_errn.txt", O_RDONLY | O_CREAT | O_TRUNC, 0644);
  std::cout << "UNKNOWN: " << ft_write(ronly, "test\n", 5) << std::endl;

  int pipefd[2];
  pipe(pipefd);
  // std::cout << "first: " << pipefd[0] << " next: " << pipefd[1] << std::endl;
  close(pipefd[0]);
  std::cout << "EPIPE: " << ft_write(pipefd[1], "test\n", 5) << std::endl;


  // Counting successful tests
  int trues = std::count(check.begin(), check.end(), true);
  print_result(trues, check.size());
}

void TestAsm::print_setup() {
  std::cout << BOLD << MAGENTA << "\n"
            << std::left << std::setw(40) << "TESTNAME" << std::right
            << std::setw(4) << "COMP\n"
            << RESET;
}

/**
 * @brief Small helper function to print which test
 * suite currently is being performed.
 *
 * @param test String for being displayed.
 */
inline void TestAsm::print_test_header(const std::string &test) {
  std::cout << YELLOW << "\n" + test + "\n" << RESET;
}

/**
 * @brief Prints the current test being carried out.
 *
 * @param nb Test within the test suite.
 * @param test Description of the test case.
 */
inline void TestAsm::print_test_case(int nb, const std::string &test) {
  std::string out = std::to_string(nb) + ". " + test;
  std::cout << std::left << std::setw(40) << out;
}

/**
 * @brief Print result from a single test.
 *
 * @param result Bool given from the IS_EQUAL macro.
 */
inline void TestAsm::print_test_result(bool result) {
  if (result) {
    std::cout << GREEN << "[OK]\n" << RESET;
  } else {
    std::cout << RED << "[KO]\n" << RESET;
  }
}

/**
 * @brief Prints how many test cases were successful.
 *
 * @param trues How many trues are in the vector.
 * @param total Total number of tests carried out.
 */
inline void TestAsm::print_result(int trues, int total) {
  std::cout << GREEN << "RESULT: " << trues << "/" << total
            << " tests were successful." << RESET << std::endl;
}
