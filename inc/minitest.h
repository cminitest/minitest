#ifndef __MINITEST_H__
#define __MINITEST_H__ 1

typedef struct MiniTestBlockStruct MiniTestBlock;
typedef struct MiniTestStruct MiniTest;

extern MiniTest minitest;

#include "common.h"
#include "macros.h"
#include "assertions.h"

char* mt_format_suites_prologue();
char* mt_format_suites_value(char* data);
char* mt_format_suites_epilogue();

char* mt_format_suite_prologue(char* name);
char* mt_format_suite_value(char* name);
char* mt_format_suite_epilogue(char* name);

char* mt_format_block_prologue(int block_depth, int block_type, char* name);
char* mt_format_block_value(int block_depth, int block_type, char* name);
char* mt_format_block_epilogue(int block_depth, int block_type, char* name);

char* mt_format_it_prologue(int block_depth, char* color, char* bullet, char* name);
char* mt_format_it_value(int block_depth, char* color, char* bullet, char* name);
char* mt_format_it_epilogue(int block_depth, char* color, char* bullet, char* name);

char* mt_format_assert_failure_value(int block_depth, char* color, char* assert_message);

char* mt_format_summary(MiniTest *mt);

typedef struct MiniTestBlockArrayStruct {
  MiniTestBlock **array;
  size_t used;
  size_t size;
} MiniTestBlockArray;

typedef struct MiniTestBlockStruct {
  char *name;
  int block_type;
  int depth;
  int assert_result;
  char *assert_message;

  MiniTestBlockArray it_blocks;
  MiniTestBlockArray children;

  void (*before)(void**);
  void (*after)(void**);

  struct MiniTestBlockStruct *previous;
} MiniTestBlock;

typedef struct MiniTestSuiteStruct {
  char *name;
  int block_type;
  int it_flag;
  void* subject;

  MiniTestBlockArray blocks;
  MiniTestBlock     *current_block;

  MiniTestBlock *current_assertion;

  void (*suite)();

  struct MiniTestSuiteStruct *next;
  struct MiniTestSuiteStruct *previous;
} MiniTestSuite;

typedef struct MiniTestStruct {
  unsigned int assertions;
  unsigned int test_cases;
  unsigned int passes;
  unsigned int failures;

  int output_format;
  int log_level;

  MiniTestSuite *suites;
  MiniTestSuite *current;

  void (*register_suite)(struct MiniTestStruct*, const char*, void*);
  void (*step_back)(struct MiniTestStruct*);
  void (*register_block)(int, struct MiniTestStruct*, const char*);
  void (*run)();
  void (*clear)(struct MiniTestStruct*);

} MiniTest;

#endif