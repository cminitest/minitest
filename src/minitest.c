#include "minitest.h"

// ============================
//          Forwards
// ============================

static void register_suite(MiniTest *mt, const char *name, void *test_case);
static void step_back(MiniTest *mt);
static void register_block(int test_type, MiniTest *mt, const char *name);

static void run_suite(MiniTestSuite *suite, MiniTest *mt);
static void run_blocks(MiniTest *mt, MiniTestBlockArray *blocks);
static void run_it_blocks(int depth, MiniTestBlockArray *blocks);

static void run_before_fixtures(MiniTest *mt, MiniTestBlock* current_block);
static void run_after_fixtures(MiniTest *mt, MiniTestBlock* current_block);

static void init_block_array(MiniTestBlockArray *a, size_t initialSize);
static void insert_block_array(MiniTestBlockArray *a, MiniTestBlock *block);
static void clear(MiniTest *mt);
static void free_suite(MiniTestSuite *suite);
static void free_block(MiniTestBlock *block);

static void init_signals(MiniTest *mt);
static void terminate_signals(MiniTest *mt);
static void capture_signal(int signal);

// ============================
//        Implementation
// ============================

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
    mt_log_debug("Block array resized \n\t\t<size: %d>", a->size);
  }
  a->array[a->used++] = block;
  mt_log_info("Block inserted into array buffer (%d/%d)", a->used, a->size);
}

static void register_suite(MiniTest *mt, const char *name, void *test_case) {
  mt_log_debug("Initializing suite \n\t\t<name: \"%s\">", name);

  MiniTestSuite *suite = malloc(sizeof(MiniTestSuite));
  suite->name = malloc(strlen(name) + 1);
  strcpy(suite->name, name);

  suite->suite = test_case;
  suite->block_type = DESCRIBE_TYPE;
  suite->next = NULL;
  suite->it_flag = 0;
  suite->current_assertion = NULL;
  suite->subject = NULL;

  init_block_array(&(suite->blocks), 1);

  MiniTestBlock *root_block = malloc(sizeof(MiniTestBlock));
  root_block->block_type = ROOT_TYPE;
  root_block->before = NULL;
  root_block->after = NULL;

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

static void run_before_fixtures(MiniTest *mt, MiniTestBlock* current_block) {
  MiniTestBlock* block = current_block;
  void (*before_fixtures[MT_MAX_FIXTURES])(void**);

  int index = 0;

  do {
    if (block->before != NULL) {
      before_fixtures[index] = block->before;
      index++;
      mt_log_debug("Running before fixture \n\t\t<address: %p> \n\t\t<block: \"%s\">", block->before, block->name == NULL ? "Root" :  block->name);
    }
    block = block->previous;
  } while(block != NULL);

  for(int i = index-1; i >= 0; i--) {
    before_fixtures[i](&(mt->current->subject));
  }
}

static void run_after_fixtures(MiniTest *mt, MiniTestBlock* current_block) {
  MiniTestBlock* block = current_block;
  do {
    if (block->after != NULL) {
      (block->after)(&(mt->current->subject));
      mt_log_debug("Running after fixture \n\t\t<address: %p> \n\t\t<block: \"%s\">", block->after, block->name == NULL ? "Root" :  block->name);
    }    
    block = block->previous;
  } while(block != NULL);
}

static void register_block(int test_type, MiniTest *mt, const char *name) {
  if (!mt->current) {
    mt_log_fatal("Block \"%s\" was created outside a describe context. All blocks must have a parent describe block.", name);
    return;
  }

  MiniTestBlock *block = malloc(sizeof(MiniTestBlock));
  block->name = malloc(strlen(name) + 1);
  strcpy(block->name, name);
  block->it_blocks.size = 0;
  block->it_blocks.used = 0;
  block->children.used = 0;
  block->assert_message = NULL;
  block->before = NULL;
  block->after = NULL;

  mt_log_debug("Initializing block \n\t\t<address: %p> \n\t\t<name: \"%s\">", block, block->name);

  if (test_type == IT_TYPE) {
    mt->test_cases += 1;
    mt->current->current_assertion = block;
    mt->current->it_flag = 1;
    if(!mt->current->current_block->it_blocks.size) {
      init_block_array(&(mt->current->current_block->it_blocks), 1);
    }
    block->block_type = IT_TYPE;
    block->assert_result = TEST_PENDING;
    insert_block_array(&(mt->current->current_block->it_blocks), block);
    run_before_fixtures(mt, mt->current->current_block);
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
      run_after_fixtures(mt, mt->current->current_block);
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

    mt_log_info(
      "Running Assertion \n\t\t<name: \"%s\"> \n\t\t<result: %s>",
      block->name,
      (block->assert_result == TEST_PENDING ? "Pending" : block->assert_result == TEST_PASS ? "Passed" : "Failed")
    );

    mt_format_it_prologue(depth, color, bullet, block->name);
    mt_format_it_value(depth, color, bullet, block->name);

    if (block->assert_result == TEST_FAILURE) {
      mt_format_assert_failure_value(depth, color, block->assert_message);
    }

    mt_format_it_epilogue(depth, color, bullet, block->name);
  }
}

static void run_blocks(MiniTest *mt, MiniTestBlockArray *blocks) {
  if (!blocks->size) { return; }

  mt_log_info("Running blocks <count: %d>", blocks->used);

  for (int i = 0; i < blocks->used; i++) {
    MiniTestBlock *block = blocks->array[i];

    mt_format_block_prologue(block->depth, block->block_type, block->name);

    if(block->block_type != ROOT_TYPE) {
      mt_log_info("Running block \n\t\t<name: \"%s\"> \n\t\t<type: %d> \n\t\t<depth: %d>", block->name, block->block_type, block->depth);
      mt_format_block_value(block->depth, block->block_type, block->name);
    }

    run_it_blocks(block->depth+1, &(block->it_blocks));

    run_blocks(mt, &(block->children));

    mt_format_block_epilogue(block->depth, block->block_type, block->name);
  }
}

static void run_suite(MiniTestSuite *suite, MiniTest *mt) {
  minitest.current = suite;

  if (!suite) { return; }

  mt_log_info("Running suite \n\t\t<name: \"%s\">", suite->name);

  mt_format_suite_prologue(suite->name);
  mt_format_suite_value(suite->name);

  suite->suite(mt);

  run_blocks(mt, &(suite->blocks));

  mt_format_suite_epilogue(suite->name);

  run_suite(suite->next, mt);
}

static void run() {
  mt_format_suites_prologue();
  mt_format_suites_value(NULL);

  minitest.init_signals(&minitest);
  run_suite(minitest.suites, &minitest);
  minitest.terminate_signals(&minitest);

  mt_format_summary(&minitest);
  mt_format_suites_epilogue();
}

static void free_block(MiniTestBlock *block) {
  if (block == NULL) { return; }

  for(int i = 0; i < block->it_blocks.used; i++) {
    free_block(block->it_blocks.array[i]);
    block->it_blocks.array[i] = NULL;
  }

  for(int i = 0; i < block->children.used; i++) {
    free_block(block->children.array[i]);
    block->children.array[i] = NULL;
  }

  free(block->name);
  if(block->assert_message) {
    free(block->assert_message);
  }
  free(block);

  block = NULL;
}

static void free_suite(MiniTestSuite *suite) {
  if (suite == NULL) { return; }

  free_suite(suite->next);

  for(int i = 0; i < suite->blocks.used; i++) {
    free_block(suite->blocks.array[i]);
  }

  free(suite->name);

  suite->current_block = NULL;
  suite->current_assertion = NULL;
  suite->next = NULL;
  suite->previous = NULL;

  free(suite);

  suite = NULL;
}

static void clear(MiniTest *mt) {
  free_suite(mt->suites);
  mt->suites = NULL;
  mt->current = NULL;
  mt->assertions = 0;
  mt->test_cases = 0;
  mt->passes = 0;
  mt->failures = 0;
}

static void capture_signal(int signal) {
  mt_log_info(
    "Signal \"%d\" was captured: \n\t Suite: %s \n\t Context: %s \n\t Test Case: %s",
    signal,
    minitest.current->name,
    minitest.current->current_block->name,
    minitest.current->current_assertion->name
  );

  minitest.failures += 1;
  minitest.current->current_assertion->assert_result = TEST_FAILURE;

  char *template = mt_assert_template(1, mt_template_value, MT_EXPECT_SIGNAL_FLAG);
  minitest.current->current_assertion->assert_message = malloc(MT_MAX_ASSERTION_BUFFER);

  char sig_str[3];
  sprintf(sig_str, "%d", signal);

  snprintf(                                                                         
    minitest.current->current_assertion->assert_message, MT_MAX_ASSERTION_BUFFER,
    template, "Signal", sig_str, ""
  );

  free(template);

  longjmp(minitest.signal_buffer, 1);
}

static void init_signals(MiniTest *mt) {
  if (mt->signals == MT_SIGNONE) { return; }

  int signals[] = MT_SIGNALS_ARRAY;
  for (int i = 0; i < MT_N_SIGNALS; i++) {
    if (mt->signals & (1 << i)) {
      signal(signals[i], capture_signal);
    }
  }
}

static void terminate_signals(MiniTest *mt) {
  if (mt->signals == MT_SIGNONE) { return; }

  int signals[] = MT_SIGNALS_ARRAY;
  for (int i = 0; i < MT_N_SIGNALS; i++) {
    if (mt->signals & (1 << i)) {
      signal(signals[i], SIG_DFL);
    }
  }
}

MiniTest minitest = {
  .assertions = 0,
  .test_cases = 0,
  .passes = 0,
  .failures = 0,
  .log_level = MT_LOG_ERROR,
  .output_format = MT_STDIO,
  .suites = NULL,
  .current = NULL,
  .register_suite = register_suite,
  .register_block = register_block,
  .step_back = step_back,
  .run = run,
  .clear = clear,
  .signals = MT_SIGNONE,
  .init_signals = init_signals,
  .terminate_signals = terminate_signals
};