#include "assertions.h"

char* mt_assert_template(int neg, char* format) {
  char* template = malloc(MT_MAX_ASSERTION_BUFFER);
  memset(template, '\0', MT_MAX_ASSERTION_BUFFER);
  sprintf(
    template,
    "Expected <" mt_template_value "> %s equal <" mt_template_value ">",
    format,
    !neg ? "to" : "to not",
    format
  );
  return template;
}

//
// general expectations
//
mt_expect(int,    int,    (actual == expected), "%i");
mt_expect(char,   char,   (actual == expected), "%c");
mt_expect(short,  short,  (actual == expected), "%i");
mt_expect(long,   long,   (actual == expected), "%ld");
mt_expect(double, double, (actual == expected), "%f");
mt_expect(float,  float,  (actual == expected), "%f");
mt_expect(ptr,    void*,  (actual == expected), "%p");
mt_expect(str,    char*,  (strcmp(actual,expected)==0), "%s");
mt_expect(sizet,  size_t, (actual == expected), "%zu");
mt_expect(uint,   unsigned int, (actual == expected), "%u");

//
// array expectations
//
mt_assert_array(int, int, (arr_1[i] == arr_2[i]));
mt_expect_array(intarr, int, __assert_array_int(expected, actual, actual_size, expected_size), NULL);