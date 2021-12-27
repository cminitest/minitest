#ifndef __MINITEST_ASSERTIONS_H__
#define __MINITEST_ASSERTIONS_H__ 1

#include "minitest.h"

#ifndef MT_MAX_ASSERTION_BUFFER
#define MT_MAX_ASSERTION_BUFFER 0x400
#endif

#define mt_template_value "%s"
char* mt_assert_template(int neg, char* format);

#define to    0
#define not   +1
#define equal(expected)      ,expected);
#define be_null  ,NULL);
#define be_false ,0);
#define be_true  ,1);

#define expect_result minitest.current->current_assertion->assert_result

#define mt_expect_forward(suffix, type) \
  void __expect_##suffix(MiniTest *mt, type actual, int negated, type expected)

#define mt_expect_definition(suffix, type, comparator, format)                      \
  void __expect_##suffix(MiniTest *mt, type actual, int negated, type expected) {   \
    mt->assertions += 1;                                                            \
    if (mt->current->current_assertion->assert_result == TEST_FAILURE) { return; }  \
    int result = negated ? !(comparator) : (comparator);                            \
    if (result) {                                                                   \
      mt->passes += 1;                                                              \
      mt->current->current_assertion->assert_result = TEST_PASS;                    \
    } else {                                                                        \
      mt->failures += 1;                                                            \
      mt->current->current_assertion->assert_result = TEST_FAILURE;                 \
      mt->current->current_assertion->assert_message = malloc(MT_MAX_ASSERTION_BUFFER); \
      char *template = mt_assert_template(negated, format);                             \
      snprintf(                                                                         \
        mt->current->current_assertion->assert_message, MT_MAX_ASSERTION_BUFFER,        \
        template, actual, expected                                                      \
      ); free(template);                                                                \
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
mt_expect_forward(sizet,  size_t);
mt_expect_forward(uint,  unsigned int);

#define expect_generic(actual) _Generic(actual,                  \
                                        int: __expect_int,       \
                                        char: __expect_char,     \
                                        short: __expect_short,   \
                                        long: __expect_long,     \
                                        double: __expect_double, \
                                        float: __expect_float,   \
                                        void*: __expect_ptr,     \
                                        char*: __expect_str,     \
                                        size_t: __expect_sizet,  \
                                        unsigned int: __expect_uint   \
                                      ) \

#define __expect_call(mt, actual) expect_generic(actual)(mt, (actual),
#define expect(actual) __expect_call(&minitest, actual)

#endif