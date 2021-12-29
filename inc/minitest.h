#ifndef __MINITEST_H__
#define __MINITEST_H__ 1

typedef struct MiniTestBlockStruct MiniTestBlock;
typedef struct MiniTestStruct MiniTest;

extern MiniTest minitest;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "macros.h"
#include "assertions.h"

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

  struct MiniTestBlockStruct *previous;
} MiniTestBlock;

typedef struct MiniTestSuiteStruct {
  char *name;
  int block_type;
  int it_flag;

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

  MiniTestSuite *suites;
  MiniTestSuite *current;

  void (*register_suite)(struct MiniTestStruct*, const char*, void*);
  void (*step_back)(struct MiniTestStruct*);
  void (*register_block)(int, struct MiniTestStruct*, const char*);
  void (*run)();
  void (*clear)(struct MiniTestStruct*);

} MiniTest;

#endif