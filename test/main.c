#include "testsuite.h"

#define EXPECTED_FAILURES 24

int main() {
  //minitest.output_format = 0xFF;
  minitest.run();

  int result = EXPECTED_FAILURES - minitest.failures;

  minitest.clear(&minitest);
  minitestmocks.clear(&minitestmocks, mt_free_mocks);

  return result;
}