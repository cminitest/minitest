#ifndef __MINITEST_TESTSUITE_H__
#define __MINITEST_TESTSUITE_H__ 1

#include "minitest/setup.h"

typedef struct ExpectExtStruct {
  int value;
} ExpectExt;

int add_ints(int n1, int n2);
int add_three_ints(int n1, int n2, int n3);

mt_setup_expect_forwards(
  mt_expect_forward(extstruct, ExpectExt*)
  mt_expect_array_forward(extstructarr, ExpectExt*)
)

#define MT_EXPECT_EXTENSIONS mt_setup_expect_extensions( \
  mt_expect_extension(extstruct, ExpectExt*)             \
  mt_expect_extension(extstructarr, ExpectExt**)         \
)

mt_setup_mocks(
  mt_param_extensions(
    mt_mock_param(ExpectExt*, expect_ext_value)
    mt_mock_param(void**, expect_void_ptrptr_value)
  ),
  mt_setup_mock_forwards(
    mt_mock_forward(add_ints, int, 2, int n1, int n2)
  )
)

#include "minitest/minitest.h"

#endif