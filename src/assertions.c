#include "assertions.h"

mt_expect_definition(int,    int,    (actual == expected), "%i");
mt_expect_definition(char,   char,   (actual == expected), "%c");
mt_expect_definition(short,  short,  (actual == expected), "%i");
mt_expect_definition(long,   long,   (actual == expected), "%l");
mt_expect_definition(double, double, (actual == expected), "%f");
mt_expect_definition(float,  float,  (actual == expected), "%f");
mt_expect_definition(ptr,    void*,  (actual == expected), "%p");
mt_expect_definition(str,    char*,  (strcmp(actual,expected)==0), "%s");
mt_expect_definition(sizet,  size_t, (actual == expected), "%zu");
mt_expect_definition(uint,   unsigned int, (actual == expected), "%u");