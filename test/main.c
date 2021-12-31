#include "testsuite.h"

#define EXPECTED_FAILURES 20

int main() {
  minitest.run();

  int result = EXPECTED_FAILURES - minitest.failures;

  minitest.clear(&minitest);

  return result;
}