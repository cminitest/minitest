#include "minitest/minitest.h"

int main() {
  //minitest.output_format = MT_XML;
  minitest.log_level = MT_LOG_DEBUG;

  minitest.run();

  minitest.clear(&minitest);

  return 0;
}