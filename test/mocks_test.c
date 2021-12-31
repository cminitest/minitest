#include "testsuite.h"

mt_define_mock(add_ints, int, int n1, int n2);

describe("MiniTest", minitest_mocks)
  context("Mocks")
    mock(add_ints) and_return(5)

    it("mocks the return value of the function")
      #ifdef LD_WRAP
        expect(add_ints(2, 2)) to equal(5)
      #else
        expect(__wrap_add_ints(2, 2)) to equal(5)
      #endif
    end

    it("can alter the return value")
      mock(add_ints) and_return(4)
      #ifdef LD_WRAP
        expect(add_ints(2, 2)) to equal(4)
      #else
        expect(__wrap_add_ints(2, 2)) to equal(4)
      #endif
    end
  end
end