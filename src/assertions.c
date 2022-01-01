#include "assertions.h"

char* mt_expect_flag_to_string(mt_expect_flags flag) {
  switch(flag) {
    case MT_EXPECT_GT_FLAG:
      return "be greater than";
    case MT_EXPECT_LT_FLAG:
      return "be less than";
    case MT_EXPECT_GTE_FLAG:
      return "be greater than or equal to";
    case MT_EXPECT_LTE_FLAG:
      return "be less than or equal to";
    case MT_EXPECT_RANGE_FLAG:
      return "be in range";
    default:
      return "equal";
  }
}

char* mt_assert_template(int neg, char* format, mt_expect_flags flag) {
  char* template = malloc(MT_MAX_ASSERTION_BUFFER);
  memset(template, '\0', MT_MAX_ASSERTION_BUFFER);

  char* range_str = (char*)malloc(15);
  memset(range_str, '\0', 15);

  if (flag == MT_EXPECT_RANGE_FLAG) {
    sprintf(range_str, "-<" mt_template_value ">", format);
  }

  sprintf(
    template,
    "Expected <" mt_template_value "> %s %s <" mt_template_value ">%s",
    format,
    !neg ? "to" : "to not",
    mt_expect_flag_to_string(flag),
    format,
    range_str
  );

  free(range_str);

  return template;
}

int __double_equal(double actual, double expected, double epsilon) {
  return fabs(actual - expected) < epsilon;
}

int __float_equal(float actual, float expected, float epsilon) {
  return fabs(actual - expected) < epsilon;
}

//
// general expectations
//
mt_expect(int,    int,    __expect_assert_int(actual,expected,max_range,flag), "%i");
mt_expect(char,   char,   __expect_assert_char(actual,expected,max_range,flag), "%c");
mt_expect(short,  short,  __expect_assert_short(actual,expected,max_range,flag), "%i");
mt_expect(long,   long,   __expect_assert_long(actual,expected,max_range,flag), "%ld");

mt_expect(double, double, (__double_equal(actual,expected,MT_EXPECT_EPSILON)), "%f");
mt_expect(float,  float,  (__float_equal(actual,expected,MT_EXPECT_EPSILON)),  "%f");

mt_expect(ptr,    void*,  __expect_assert_ptr(actual,expected,max_range,flag), "%p");
mt_expect(str,    char*,  (strcmp(actual,expected)==0), "%s");

// also unsigned long
mt_expect(sizet,  size_t, __expect_assert_sizet(actual,expected,max_range,flag), "%zu");

mt_expect(uint,     unsigned int,    __expect_assert_uint(actual,expected,max_range,flag),    "%u");
mt_expect(ushort,   unsigned short,  __expect_assert_ushort(actual,expected,max_range,flag),  "%u");
mt_expect(uchar,    unsigned char,   __expect_assert_uchar(actual,expected,max_range,flag),   "%d");

//
// array expectations
//
mt_assert_array(int, int, (arr_1[i] == arr_2[i]));
mt_expect_array(intarr, int, __assert_array_int(expected, actual, actual_size, expected_size), NULL);

mt_assert_array(short, short, (arr_1[i] == arr_2[i]));
mt_expect_array(shortarr, short, __assert_array_short(expected, actual, actual_size, expected_size), NULL);

mt_assert_array(long, long, (arr_1[i] == arr_2[i]));
mt_expect_array(longarr, long, __assert_array_long(expected, actual, actual_size, expected_size), NULL);

mt_assert_array(double, double, (__double_equal(arr_1[i],arr_2[i],MT_EXPECT_EPSILON)) );
mt_expect_array(doublearr, double, __assert_array_double(expected, actual, actual_size, expected_size), NULL);

mt_assert_array(float, float, (__float_equal(arr_1[i],arr_2[i],MT_EXPECT_EPSILON)) );
mt_expect_array(floatarr, float, __assert_array_float(expected, actual, actual_size, expected_size), NULL);

