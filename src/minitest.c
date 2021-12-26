#include "minitest.h"

// ============================
//          Forwards
// ============================

static void register_suite(MiniTest *mt, const char *name, void *test_case);
static void step_back(MiniTest *mt);
static void register_block(int test_type, MiniTest *mt, const char *name);

static void run_suite(MiniTestSuite *suite);
static void run_blocks(MiniTestBlockArray *blocks);
static void run_it_blocks(int depth, MiniTestBlockArray *blocks);

static void init_block_array(MiniTestBlockArray *a, size_t initialSize);
static void insert_block_array(MiniTestBlockArray *a, MiniTestBlock *block);
static char* type_to_string(int t);

// ============================
//        Implementation
// ============================

#define ROOT_TYPE 0x00
#define DESCRIBE_TYPE 0x01
#define IT_TYPE 0x02
#define CONTEXT_TYPE 0x03
#define GIVEN_TYPE 0x04
#define AND_TYPE 0x05
#define WHEN_TYPE 0x06

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
    default:
      return "test";
  }
}

static void init_block_array(MiniTestBlockArray *a, size_t initialSize) {
  a->array = (malloc(initialSize * sizeof(MiniTestBlock*)));
  a->used = 0;
  a->size = initialSize;
}

static void insert_block_array(MiniTestBlockArray *a, MiniTestBlock *block) {
  if (a->used == a->size) {
    // 3 / 2 gives you 50% worst and 25% typical
    // + 8 for arrays which are reasonably small don't end up doing too many copies
    a->size = (a->size * 3) / 2 + 8;
    a->array = (realloc(a->array, a->size * sizeof(MiniTestBlock*)));
  }
  a->array[a->used++] = block;
}

static void register_suite(MiniTest *mt, const char *name, void *test_case) {
  MiniTestSuite *suite = malloc(sizeof(MiniTestSuite));
  suite->name = malloc(strlen(name) + 1);
  strcpy(suite->name, name);

  suite->suite = test_case;
  suite->block_type = DESCRIBE_TYPE;
  suite->next = NULL;
  suite->it_flag = 0;
  suite->current_assertion = NULL;

  init_block_array(&(suite->blocks), 1);

  MiniTestBlock *root_block = malloc(sizeof(MiniTestBlock));
  root_block->block_type = ROOT_TYPE;

  insert_block_array(&(suite->blocks), root_block);

  suite->current_block = suite->blocks.array[0];

  if (mt->current == NULL) {
    mt->current = suite;
    mt->suites = suite;
  } else {
    mt->current->next = suite;
    mt->current = suite;
  }
}

static void register_block(int test_type, MiniTest *mt, const char *name) {
  if (!mt->current) {
    // todo: errors
    return;
  }

  MiniTestBlock *block = malloc(sizeof(MiniTestBlock));
  block->name = malloc(strlen(name) + 1);
  strcpy(block->name, name);

  if (test_type == IT_TYPE) {
    mt->current->current_assertion = block;
    mt->current->it_flag = 1;
    if(!mt->current->current_block->it_blocks.size) {
      init_block_array(&(mt->current->current_block->it_blocks), 1);
    }
    block->block_type = IT_TYPE;
    block->assert_result = TEST_PENDING;
    insert_block_array(&(mt->current->current_block->it_blocks), block);
  } else {
    block->block_type = test_type;
    block->previous   = mt->current->current_block;
    block->depth      = mt->current->current_block->depth + 1;

    if(!mt->current->current_block->children.size) {
      init_block_array(&(mt->current->current_block->children), 1);
    }

    insert_block_array(&(mt->current->current_block->children), block);

    mt->current->current_block = block;
  }
}

static void step_back(MiniTest *mt) {
  if (mt->current) {
    if (mt->current->it_flag) {
      mt->current->it_flag = 0;
      return;
    }
    if (mt->current->current_block && mt->current->current_block->previous) {
      mt->current->current_block = mt->current->current_block->previous;
    }
  }
}

static void run_it_blocks(int depth, MiniTestBlockArray *blocks) {
  if (!blocks->size) { return; }

  for (int i = 0; i < blocks->used; i++) {
    MiniTestBlock *block = blocks->array[i];

    char *color = block->assert_result == TEST_PENDING ? CONSOLE_CYAN : block->assert_result == TEST_PASS ? CONSOLE_GREEN : CONSOLE_RED;
    char *bullet = block->assert_result == TEST_PENDING ? PENDING_BULLET : block->assert_result == TEST_PASS ? SUCCESS_BULLET : FAILURE_BULLET;

    printf("%*c %s %s it %s %s\n", depth*2, ' ', color, bullet, block->name, CONSOLE_DEFAULT);
  }
}

static void run_blocks(MiniTestBlockArray *blocks) {
  if (!blocks->size) { return; }

  for (int i = 0; i < blocks->used; i++) {
    MiniTestBlock *block = blocks->array[i];
    if(block->block_type != ROOT_TYPE) {
      printf("%*c %s %s %s %s\n", block->depth*2, ' ', CONSOLE_GREEN, type_to_string(block->block_type), CONSOLE_DEFAULT, block->name);
    }
    run_it_blocks(block->depth+1, &(block->it_blocks));
    run_blocks(&(block->children));
  }
}

static void run_suite(MiniTestSuite *suite) {
  if (!suite) { return; }

  suite->suite();

  printf("%s describe %s %s:\n", CONSOLE_YELLOW, CONSOLE_DEFAULT, suite->name);

  run_blocks(&(suite->blocks));

  run_suite(suite->next);
}

static void run() {
  minitest.current = minitest.suites;
  run_suite(minitest.current);
}

MiniTest minitest = {
  .assertions = 0,
  .test_cases = 0,
  .passes = 0,
  .failures = 0,
  .suites = NULL,
  .current = NULL,
  .register_suite = register_suite,
  .register_block = register_block,
  .step_back = step_back,
  .run = run
};