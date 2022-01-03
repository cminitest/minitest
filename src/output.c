#include "minitest.h"

static char* type_to_string(int t);

static char* type_to_string(int t) {
  switch(t) {
    case IT_TYPE:
      return "it";
    case CONTEXT_TYPE:
      return "context";
    case GIVEN_TYPE:
      return "given";
    case AND_TYPE:
      return "and";
    case WHEN_TYPE:
      return "when";
    case ROOT_TYPE:
      return "root";
    default:
      return "undefined";
  }
}

char* mt_format_suite_output(char* name) {
  switch(minitest.output_format) {
    case MT_STDIO:
      printf("%s describe %s %s:\n", CONSOLE_YELLOW, CONSOLE_DEFAULT, name);
      return NULL;
    default:
      return NULL;
  }
}

char* mt_format_block_output(int block_depth, int block_type, char* name) {
  switch(minitest.output_format) {
    case MT_STDIO:
      printf("%*c %s %s %s %s\n", block_depth*2, ' ', CONSOLE_GREEN, type_to_string(block_type), CONSOLE_DEFAULT, name);
      return NULL;
    default:
      return NULL;
  }
}

char* mt_format_it_output(int block_depth, char* color, char* bullet, char* name) {
  switch(minitest.output_format) {
    case MT_STDIO:
      printf("%*c %s %s it %s %s\n", block_depth*2, ' ', color, bullet, name, CONSOLE_DEFAULT);
      return NULL;
    default:
      return NULL;
  }
}

char* mt_format_assert_failure_output(int block_depth, char* color, char* assert_message) {
  switch(minitest.output_format) {
    case MT_STDIO:
      printf("%*c %s %s %s\n", block_depth*2, ' ', color, assert_message, CONSOLE_DEFAULT);
      return NULL;
    default:
      return NULL;
  }
}