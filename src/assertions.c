#include "assertions.h"

void __expect(MiniTest *mt, int actual, int negated, int expected) {
  if (mt->current->current_assertion->assert_result == TEST_FAILURE) { return; }
  if (negated) {
    if (actual != expected) {
      mt->current->current_assertion->assert_result = TEST_PASS;
    } else {
      mt->current->current_assertion->assert_result = TEST_FAILURE;
    }
  } else {
    if (actual == expected) {
      mt->current->current_assertion->assert_result = TEST_PASS;
    } else {
      mt->current->current_assertion->assert_result = TEST_FAILURE;
    }
  }
}