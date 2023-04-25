#include "testsuite.h"

int main() {
  //minitest.output_format = MT_XML;
  //minitest.log_level = MT_LOG_DEBUG;
  minitest.signals = MT_SIGFPE | MT_SIGSEGV;

  minitest.run();

  int result = EXPECTED_FAILURES - minitest.failures;

  minitest.clear(&minitest);

  return result;
}