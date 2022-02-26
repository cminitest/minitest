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

//
// Suites Prologue, output, epilogue
//
char* mt_format_suites_prologue() {
  switch(minitest.output_format) {
    case MT_XML:
      printf("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
      printf("<testsuites>");
      return NULL;
    default:
      return NULL;
  }
}

char* mt_format_suites_value(char* data) {
  return NULL;
}

char* mt_format_suites_epilogue() {
  switch(minitest.output_format) {
    case MT_XML:
      printf("</testsuites>");
      return NULL;
    default:
      return NULL;
  }
}

//
// Suite Prologue, output, epilogue
//
char* mt_format_suite_prologue(char* name) {
  switch(minitest.output_format) {
    case MT_XML:
      printf("<testsuite name=\"%s\">", name);
      return NULL;
    default:
      return NULL;
  }
}

char* mt_format_suite_value(char* name) {
  switch(minitest.output_format) {
    case MT_STDIO:
      printf("%s describe %s %s:\n", CONSOLE_YELLOW, CONSOLE_DEFAULT, name);
      return NULL;
    default:
      return NULL;
  }
}

char* mt_format_suite_epilogue(char* name) {
  switch(minitest.output_format) {
    case MT_XML:
      printf("</testsuite>");
      return NULL;
    default:
      return NULL;
  }
}

//
// Block Prologue, output, epilogue
//
char* mt_format_block_prologue(int block_depth, int block_type, char* name) {
  if (name == NULL) { return NULL; }
  switch(minitest.output_format) {
    case MT_XML:
      printf("<testsuite id=\"%s\" name=\"%s\">", type_to_string(block_type), name);
      return NULL;
    default:
      return NULL;
  }
}

char* mt_format_block_value(int block_depth, int block_type, char* name) {
  switch(minitest.output_format) {
    case MT_STDIO:
      printf("%*c %s %s %s %s\n", block_depth*2, ' ', CONSOLE_GREEN, type_to_string(block_type), CONSOLE_DEFAULT, name);
      return NULL;
    default:
      return NULL;
  }
}

char* mt_format_block_epilogue(int block_depth, int block_type, char* name) {
  if (name == NULL) { return NULL; }
  switch(minitest.output_format) {
    case MT_XML:
      printf("</testsuite>");
      return NULL;
    default:
      return NULL;
  }
}

//
// It Prologue, output, epilogue
//

char* mt_format_it_prologue(int block_depth, char* color, char* bullet, char* name) {
  switch(minitest.output_format) {
    case MT_XML:
      printf("<testcase name=\"%s\">", name);
      return NULL;
    default:
      return NULL;
  }
}

char* mt_format_it_value(int block_depth, char* color, char* bullet, char* name) {
  switch(minitest.output_format) {
    case MT_STDIO:
      printf("%*c %s %s it %s %s\n", block_depth*2, ' ', color, bullet, name, CONSOLE_DEFAULT);
      return NULL;
    default:
      return NULL;
  }
}

char* mt_format_it_epilogue(int block_depth, char* color, char* bullet, char* name) {
  switch(minitest.output_format) {
    case MT_XML:
      printf("</testcase>");
      return NULL;
    default:
      return NULL;
  }
}

//
// Assertion Result
//

char* mt_format_assert_failure_value(int block_depth, char* color, char* assert_message) {
  switch(minitest.output_format) {
    case MT_STDIO:
      printf("%*c %s %s %s\n", block_depth*2, ' ', color, assert_message, CONSOLE_DEFAULT);
      return NULL;
    case MT_XML:
      printf("<failure>%s</failure>", assert_message);
      return NULL;
    default:
      return NULL;
  }
}

//
// Summary
//

char* mt_format_summary(MiniTest *mt) {
  switch(minitest.output_format) {
    case MT_STDIO:
      printf(
        "\n%d tests, %d assertions, %s%d failures%s\n\n",
        mt->test_cases,
        mt->assertions,
        CONSOLE_RED,
        mt->failures,
        CONSOLE_DEFAULT
      );
      return NULL;
    default:
      return NULL;
  }
}