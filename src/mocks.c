#include "minitest.h"

static void mt_clear_mocks(MiniTestMockSuite *s, void (*handle)(MiniTestMock*)) {
  s->nodes = NULL;
  handle(s->nodes);
}

MiniTestMockSuite minitestmocks = {
  .nodes = NULL,
  .clear = mt_clear_mocks
};