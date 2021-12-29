#ifndef __MINITEST_ASSERTIONS_H__
#define __MINITEST_ASSERTIONS_H__ 1

#include "minitest.h"

typedef enum { 
  NONE, 
  SINGLE, 
  ARRAY 
} mt_format;

#ifndef MT_MAX_ASSERTION_BUFFER
#define MT_MAX_ASSERTION_BUFFER 0x400
#endif

#ifndef MT_EXPECT_EXT
#define MT_EXPECT_EXT
#endif

#define mt_template_value "%s"
char* mt_assert_template(int neg, char* format);

#define to    0
#define not   +1
#define equal(expected)      ,expected, sizeof(expected));
#define be_null  ,NULL, 0);
#define be_false ,0, 0);
#define be_true  ,1, 0);

#define expect_result minitest.current->current_assertion->assert_result

#define mt_expect_forward(suffix, type) \
  void __expect_##suffix(MiniTest *mt, type actual, size_t as, int negated, type expected, size_t es)

#define mt_expect_array_forward(suffix, type) \
  void __expect_##suffix(MiniTest *mt, type actual[], size_t as, int negated, type expected[], size_t es)

#define default_format_handle(suffix, type, arr, tf) default_format_handle_definition_##tf(suffix, type, arr)
#define default_format_handle_definition_NONE(suffix, type, arr)
#define default_format_handle_definition_SINGLE(suffix, type, arr) type  __format_##suffix(type value arr) { return value; }
#define default_format_handle_definition_ARRAY(suffix, type, arr) type* __format_##suffix(type value arr) { return value; }

#define mt_expect_definition(suffix, type, arr, comparator, format, handle_type) \
  default_format_handle(suffix, type, arr, handle_type)                          \
  void __expect_##suffix(MiniTest *mt, type actual arr, size_t actual_size, int negated, type expected arr, size_t expected_size) {   \
    mt->assertions += 1;                                                            \
    if (mt->current->current_assertion->assert_result == TEST_FAILURE) { return; }  \
    int result = negated ? !(comparator) : (comparator);                            \
    if (result) {                                                                   \
      mt->passes += 1;                                                              \
      mt->current->current_assertion->assert_result = TEST_PASS;                    \
    } else {                                                                        \
      mt->failures += 1;                                                            \
      mt->current->current_assertion->assert_result = TEST_FAILURE;                 \
      if(format == NULL) { return; }                                                    \
      mt->current->current_assertion->assert_message = malloc(MT_MAX_ASSERTION_BUFFER); \
      char *template = mt_assert_template(negated, format);                             \
      snprintf(                                                                         \
        mt->current->current_assertion->assert_message, MT_MAX_ASSERTION_BUFFER,        \
        template, __format_##suffix (actual), __format_##suffix (expected)              \
      ); free(template);                                                                \
    }                                                                                   \
  }                                                                                     \

//
// todo: __compare_array won't work for strings or pointers
//
#define mt_assert_array(suffix, type, comparator) \
  int __compare_array_##suffix(const void * a, const void *b) {                         \
    return (*(type*)a - *(type*)b);                                                     \
  }                                                                                     \
  int __assert_array_##suffix(type arr_1[], type arr_2[], size_t s1, size_t s2) {       \
    if (s1/sizeof(type) != s2/sizeof(type)) { return 0; }                               \
    qsort(arr_1, s1/sizeof(type), sizeof(type), __compare_array_##suffix);              \
    qsort(arr_2, s2/sizeof(type), sizeof(type), __compare_array_##suffix);              \
    int result = 1;                                                                     \
    for(int i = 0; i < s1/sizeof(type); i++) {                                          \
      if(!comparator) { result = 0; break; }                                            \
    }                                                                                   \
    return result;                                                                      \
  }                                                                                     \

#define mt_expect(suffix, type, comparator, format) mt_expect_definition(suffix, type,, comparator, format, SINGLE)
#define mt_expect_array(suffix, type, comparator, format) mt_expect_definition(suffix, type, [], comparator, format, ARRAY)

#define mt_expect_ext(suffix, type, comparator, format) mt_expect_definition(suffix, type,, comparator, format, NONE)
#define mt_expect_array_ext(suffix, type, comparator, format) mt_expect_definition(suffix, type, [], comparator, format, NONE)

mt_expect_forward(int,    int);
mt_expect_forward(char,   char);
mt_expect_forward(short,  short);
mt_expect_forward(long,   long);
mt_expect_forward(double, double);
mt_expect_forward(float,  float);
mt_expect_forward(ptr,    void*);
mt_expect_forward(str,    char*);
mt_expect_forward(sizet,  size_t);
mt_expect_forward(uint,   unsigned int);

mt_expect_array_forward(intarr, int);

#define expect_generic(actual) _Generic(actual,                  \
                                        MT_EXPECT_EXT            \
                                        int: __expect_int,       \
                                        char: __expect_char,     \
                                        short: __expect_short,   \
                                        long: __expect_long,     \
                                        double: __expect_double, \
                                        float: __expect_float,   \
                                        void*: __expect_ptr,     \
                                        char*: __expect_str,     \
                                        size_t: __expect_sizet,  \
                                        unsigned int: __expect_uint,   \
                                        int*: __expect_intarr         \
                                      ) \

#define __expect_call(mt, actual) expect_generic(actual)(mt, (actual), (sizeof(actual)),
#define expect(actual) __expect_call(&minitest, actual)

#endif