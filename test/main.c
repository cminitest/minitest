#include "testsuite.h"

#define EXPECTED_FAILURES 24

mt_mocks_initialize()

int main() {
  minitest.run();

  int result = EXPECTED_FAILURES - minitest.failures;

  minitest.clear(&minitest);

  return result;
}