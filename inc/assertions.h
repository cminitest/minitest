#ifndef __MINITEST_ASSERTIONS_H__
#define __MINITEST_ASSERTIONS_H__ 1

#include "minitest.h"

#define to    0
#define not   +1
#define equal(expected)      ,expected);
#define expect_result minitest.current->current_assertion->assert_result

#define mt_expect_forward(suffix, type) \
  void __expect_##suffix(MiniTest *mt, type actual, int negated, type expected)

#define mt_expect_definition(suffix, type, comparator, format)                      \
  void __expect_##suffix(MiniTest *mt, type actual, int negated, type expected) {   \
    if (mt->current->current_assertion->assert_result == TEST_FAILURE) { return; }  \
    int result = negated ? !(comparator) : (comparator);                            \
    if (result) {                                                                   \
      mt->current->current_assertion->assert_result = TEST_PASS;                    \
    } else {                                                                        \
      mt->current->current_assertion->assert_result = TEST_FAILURE;                 \
    }                                                                               \
  }                                                                                 \

mt_expect_forward(int,    int);
mt_expect_forward(char,   char);
mt_expect_forward(short,  short);
mt_expect_forward(long,   long);
mt_expect_forward(double, double);
mt_expect_forward(float,  float);
mt_expect_forward(ptr,    void*);
mt_expect_forward(str,    char*);

#define expect_generic(actual) _Generic(actual,                  \
                                        int: __expect_int,       \
                                        char: __expect_char,     \
                                        short: __expect_short,   \
                                        long: __expect_long,     \
                                        double: __expect_double, \
                                        float: __expect_float,   \
                                        void*: __expect_ptr,     \
                                        char*: __expect_str      \
                                      ) \

#define __expect_call(mt, actual) expect_generic(actual)(mt, (actual),
#define expect(actual) __expect_call(&minitest, actual)

#endif