#ifndef __MINITEST_TESTSUITE_H__
#define __MINITEST_TESTSUITE_H__ 1

#include "minitest/extensions.h"

typedef struct ExpectExtStruct {
  int value;
} ExpectExt;

mt_setup_expect_forwards(
  mt_expect_forward(extstruct, ExpectExt*)
  mt_expect_array_forward(extstructarr, ExpectExt*)
)

#define MT_EXPECT_EXTENSIONS mt_setup_expect_extensions( \
  mt_expect_extension(extstruct, ExpectExt*)             \
  mt_expect_extension(extstructarr, ExpectExt**)         \
)

#include "minitest/minitest.h"

#endif