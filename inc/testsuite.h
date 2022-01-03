#ifndef __MINITEST_TESTSUITE_H__
#define __MINITEST_TESTSUITE_H__ 1

typedef struct ExpectExtStruct {
  int value;
} ExpectExt;

#define MT_EXPECT_EXT \
  mt_register_expect_extension(extstruct, ExpectExt*) \
  mt_register_expect_extension(extstructarr, ExpectExt**)

#include "minitest/minitest.h"

int add_ints(int n1, int n2);
int add_three_ints(int n1, int n2, int n3);

mt_expect_forward(extstruct, ExpectExt*);
mt_expect_array_forward(extstructarr, ExpectExt*);

mt_mock_forwards(add_ints, int, int n1, int n2);

#endif