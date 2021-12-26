#ifndef __MINITEST_ASSERTIONS_H__
#define __MINITEST_ASSERTIONS_H__ 1

#include "minitest.h"

void __expect(MiniTest *mt, int actual, int negated, int expected);

#define __expect_call(mt, actual)   __expect(mt, (actual),
#define expect(actual) __expect_call(&minitest, actual)

#define to    0
#define not   +1
#define equal(expected)      ,expected)

#endif