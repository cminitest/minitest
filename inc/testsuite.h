#ifndef __MINITEST_TESTSUITE_H__
#define __MINITEST_TESTSUITE_H__ 1

typedef struct ExpectExtStruct {
  int value;
} ExpectExt;

#define MT_EXPECT_EXT \
  ExpectExt*: __expect_extstruct,

#include "minitest/minitest.h"

mt_expect_forward(extstruct, ExpectExt*);

#endif