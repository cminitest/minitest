#include "testsuite.h"

describe("MiniTest", minitest_extensions)
  context("Extensions")
    context("SINGLE")
      ExpectExt subject = { .value = 1 };
      it("creates the expectation for the extension")
        ExpectExt comp = { .value = 1 };
        expect(&subject) to equal(&comp)
        comp.value = 2;
        expect(&subject) to not equal(&comp)
      end
    end

    context("ARRAY")
      ExpectExt* subject[] = { NULL, NULL };
      it("creates the expectation for the extension")
        ExpectExt* comp[] = { NULL, NULL };
        expect(subject) to equal(comp)
      end
    end  
  end
end