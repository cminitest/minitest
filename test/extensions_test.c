#include "testsuite.h"

int __format_extstruct(ExpectExt* extstruct) {
  return extstruct->value;
}

mt_expect_ext(extstruct, ExpectExt*, (actual->value == expected->value), "%i");

describe("MiniTest", minitest_extensions)
  context("Extensions")
    ExpectExt subject = { .value = 1 };
    it("creates the expectation for the extension")
      ExpectExt comp = { .value = 1 };
      expect(&subject) to equal(&comp)
      comp.value = 2;
      expect(&subject) to not equal(&comp)
    end
  end
end