#ifndef __MINITEST_ASSERTIONS_H__
#define __MINITEST_ASSERTIONS_H__ 1

#include "minitest.h"

typedef enum { 
  NONE,
  SINGLE,
  ARRAY,
  EXTENSION
} mt_format;

typedef enum { 
  MT_EXPECT_EQUAL_FLAG,
  MT_EXPECT_GT_FLAG,
  MT_EXPECT_LT_FLAG,
  MT_EXPECT_GTE_FLAG,
  MT_EXPECT_LTE_FLAG,
  MT_EXPECT_RANGE_FLAG,
  MT_EXPECT_BEEN_CALLED_FLAG,
  MT_EXPECT_CALLED_WITH_FLAG,
} mt_expect_flags;

#ifndef MT_MAX_ASSERTION_BUFFER
#define MT_MAX_ASSERTION_BUFFER 0x400
#endif

#ifndef MT_EXPECT_EXT
#define MT_EXPECT_EXT
#endif

#ifndef MT_EXPECT_EPSILON
#define MT_EXPECT_EPSILON 0.000001
#endif

#define mt_template_value "%s"
char* mt_assert_template(int neg, char* format, mt_expect_flags flag);
char* mt_expect_flag_to_string(mt_expect_flags flag);

#define mt_expect_epilogue if(current_expect != NULL) { current_expect = NULL; }

#define have
#define be
#define been
#define to    0
#define not   +1
#define equal(expected)      ,expected, sizeof(expected), expected, sizeof(expected), MT_EXPECT_EQUAL_FLAG); mt_expect_epilogue;

#define be_null  ,NULL, 0,0,0, MT_EXPECT_EQUAL_FLAG); mt_expect_epilogue;
#define be_false ,0, 0,0,0, MT_EXPECT_EQUAL_FLAG); mt_expect_epilogue;
#define be_true  ,1, 0,0,0, MT_EXPECT_EQUAL_FLAG); mt_expect_epilogue;
#define been_called ,0,0,0,0, MT_EXPECT_BEEN_CALLED_FLAG); mt_expect_epilogue;
#define called_with(...) ,__expect_create_mock_params(current_expect, ((MiniTestMock*)current_expect)->last_call->n_args, __VA_ARGS__),0,0,0,MT_EXPECT_CALLED_WITH_FLAG); mt_expect_epilogue;

#define greater_than(expected) ,expected,0,expected,0,MT_EXPECT_GT_FLAG); mt_expect_epilogue;
#define less_than(expected) ,expected,0,expected,0,MT_EXPECT_LT_FLAG); mt_expect_epilogue;
#define greater_than_or_equal_to(expected) ,expected,0,expected,0,MT_EXPECT_GTE_FLAG); mt_expect_epilogue;
#define less_than_or_equal_to(expected) ,expected,0,expected,0,MT_EXPECT_LTE_FLAG); mt_expect_epilogue;

#define in_range(min_range, max_range) ,min_range,0,max_range,0,MT_EXPECT_RANGE_FLAG); mt_expect_epilogue;

#define expect_result minitest.current->current_assertion->assert_result

#define mt_expect_forward(suffix, type) \
  void __expect_##suffix(MiniTest *mt, type actual, size_t as, int negated, type expected, size_t es, type max_range, size_t ms, mt_expect_flags flag)

#define mt_expect_array_forward(suffix, type) \
  void __expect_##suffix(MiniTest *mt, type actual[], size_t as, int negated, type expected[], size_t es, type max_range[], size_t ms, mt_expect_flags flag)

#define default_format_handle(suffix, type, arr, tf) default_format_handle_definition_##tf(suffix, type, arr)
#define default_format_handle_definition_NONE(suffix, type, arr) void* __format_##suffix(type value arr) { return NULL; }
#define default_format_handle_definition_SINGLE(suffix, type, arr) type  __format_##suffix(type value arr) { return value; }
#define default_format_handle_definition_ARRAY(suffix, type, arr) type* __format_##suffix(type value arr) { return value; }
#define default_format_handle_definition_EXTENSION(suffix, type, arr)

#define mt_expect_definition(suffix, type, arr, comparator, format, handle_type) \
                                                                                 \
  int __expect_assert_##suffix(type actual arr, type expected arr, type max_range arr, mt_expect_flags flag) { \
    switch(flag) {                                                                         \
      case MT_EXPECT_GT_FLAG:                                                              \
        return (actual > expected);                                                        \
      case MT_EXPECT_LT_FLAG:                                                              \
        return (actual < expected);                                                        \
      case MT_EXPECT_GTE_FLAG:                                                             \
        return (actual >= expected);                                                       \
      case MT_EXPECT_LTE_FLAG:                                                             \
        return (actual <= expected);                                                       \
      case MT_EXPECT_RANGE_FLAG:                                                           \
        return ( (actual >= expected) && (actual <= max_range) );                          \
      default:                                                                             \
        return (actual == expected);                                                       \
    }                                                                                      \
  }                                                                                        \
  mt_expect_handle(suffix, type, type, type, arr, comparator, format, handle_type)         \

#define mt_expect_handle(suffix, actual_type, expected_type, range_type, arr, comparator, format, handle_type) \
  default_format_handle(suffix, expected_type, arr, handle_type)                                               \
                                                                                                               \
  void __expect_##suffix(MiniTest *mt, actual_type actual arr, size_t actual_size, int negated, expected_type expected arr, size_t expected_size, range_type max_range arr, size_t max_range_size, mt_expect_flags flag) {   \
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
      char *template = mt_assert_template(negated, format, flag);                       \
      snprintf(                                                                         \
        mt->current->current_assertion->assert_message, MT_MAX_ASSERTION_BUFFER,        \
        template, __format_##suffix (actual), __format_##suffix (expected),             \
                  __format_##suffix (max_range)                                         \
      ); free(template);                                                                \
    }                                                                                   \
  }                                                                                     \

//
// todo: __compare_array won't work for strings or pointers
//
#define mt_assert_array(suffix, type, comparator) \
  int __compare_array_##suffix(const void * a, const void *b) {                         \
    type fa = *(const type*) a;                                                         \
    type fb = *(const type*) b;                                                         \
    return (fa > fb) - (fa < fb);                                                       \
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

#define mt_expect_ext(suffix, type, comparator, format) mt_expect_definition(suffix, type,, comparator, format, EXTENSION)
#define mt_expect_array_ext(suffix, type, comparator, format) mt_expect_definition(suffix, type, [], comparator, format, EXTENSION)

#define mt_expect_ext_default(suffix, type, comparator, format) mt_expect_definition(suffix, type,, comparator, format, NONE)
#define mt_expect_array_ext_default(suffix, type, comparator, format) mt_expect_definition(suffix, type, [], comparator, format, NONE)

#define mt_register_expect_extension(symbol, datatype)  datatype: __expect_##symbol,

mt_expect_forward(int,    int);
mt_expect_forward(char,   char);
mt_expect_forward(short,  short);
mt_expect_forward(long,   long);
mt_expect_forward(double, double);
mt_expect_forward(float,  float);
mt_expect_forward(ptr,    void*);
mt_expect_forward(str,    char*);

// also unsigned long
mt_expect_forward(sizet,  size_t);
mt_expect_forward(uint,     unsigned int);
mt_expect_forward(ushort,   unsigned short);
mt_expect_forward(uchar,    unsigned char);

mt_expect_array_forward(intarr, int);
mt_expect_array_forward(shortarr, short);
mt_expect_array_forward(longarr, long);
mt_expect_array_forward(doublearr, double);
mt_expect_array_forward(floatarr, float);

//
// mocks to support custom assertion types
//
void __set_expect_noop(int valid, ...);
void __set_current_expectation(int valid, MiniTestMock* mock, void** current_expect);
extern void __expect_mock(MiniTest*, MiniTestMock*, size_t, int, void*, size_t, void*, size_t, mt_expect_flags);
extern MockParam* __expect_create_mock_params(MiniTestMock*, int, ...);

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
                                        unsigned int: __expect_uint,     \
                                        unsigned short: __expect_ushort, \
                                        unsigned char: __expect_uchar,   \
                                        int*: __expect_intarr,         \
                                        short*: __expect_shortarr,     \
                                        long*: __expect_longarr,       \
                                        double*: __expect_doublearr,   \
                                        float*: __expect_floatarr,     \
                                        MiniTestMock*: __expect_mock   \
                                      ) \

#define mt_set_current_expectation(actual, ce) _Generic(actual, MiniTestMock*: __set_current_expectation, default: __set_expect_noop)(1,actual, ce);

#define __expect_call(mt, actual) expect_generic(actual)(mt, (actual), (sizeof(actual)),
#define expect(actual)               \
  mt_set_current_expectation(actual, &current_expect) \
  __expect_call(&minitest, actual)   \

#endif