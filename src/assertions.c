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

mt_expect_definition(int,    int,    (actual == expected), "%i");
mt_expect_definition(char,   char,   (actual == expected), "%c");
mt_expect_definition(short,  short,  (actual == expected), "%i");
mt_expect_definition(long,   long,   (actual == expected), "%ld");
mt_expect_definition(double, double, (actual == expected), "%f");
mt_expect_definition(float,  float,  (actual == expected), "%f");
mt_expect_definition(ptr,    void*,  (actual == expected), "%p");
mt_expect_definition(str,    char*,  (strcmp(actual,expected)==0), "%s");
mt_expect_definition(sizet,  size_t, (actual == expected), "%zu");
mt_expect_definition(uint,   unsigned int, (actual == expected), "%u");