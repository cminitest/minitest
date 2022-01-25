#include "testsuite.h"

typedef struct FixtureStateStruct {
  int value;
} FixtureState;

int after_all_calls = 0;

define_fixture(before, before_all_scoping) {
  FixtureState *state = malloc(sizeof(FixtureState));
  *subject = state;
}

define_fixture(before, before_nested_scoping) {
  FixtureState *state = *subject;
  state->value = 255;
  *subject = state;
}

define_fixture(after, after_all_scoping) {
  FixtureState *state = *subject;
  free(state);

  *subject = NULL;

  after_all_calls++;
}

describe("MiniTest", minitest_fixtures)

  before(before_all_scoping)
  after(after_all_scoping)

  context("fixtures")
    it("sets the FixtureState to the subject")
      void* state = subject();
      expect(state) to not be_null
    end

    when("a fixture is nested")
      before(before_nested_scoping)

      it("sets the fixture state")
        expect(((FixtureState*)subject())->value) to equal(255)
      end
    end
  end

  context("after all")
    it("has been called")
      expect(after_all_calls) to be greater_than(0)
    end
  end
end