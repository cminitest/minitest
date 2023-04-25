#include "testsuite.h"

describe("MiniTest", minitest_signals)
  context("Signals")
    when("a signal is captured")
      it("reports the error")
        MiniTest* subject = NULL;
        expect(subject->signals) to equal(0)
      end
    end

    when("the signal was captured")
      it("runs the next test")
        expect(0) to equal(0)
      end
    end
  end
end