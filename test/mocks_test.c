#include "testsuite.h"

mt_define_mock(add_ints, int, int n1, int n2);

describe("MiniTest", minitest_mocks)
  context("Mocks")
    when("the function is mocked")
      mock(add_ints) and_return(5)
  
      it("mocks the return value of the function")
        #if LD_WRAP
          expect(add_ints(2, 2)) to equal(5)
        #else
          expect(__wrap_add_ints(2, 2)) to equal(5)
        #endif
      end
  
      it("can alter the return value")
        mock(add_ints) and_return(3)
        #if LD_WRAP
          expect(add_ints(2, 2)) to equal(3)
        #else
          expect(__wrap_add_ints(2, 2)) to equal(3)
        #endif
      end
    end

    when("the original mocked function is retrieved")
      it("returns the original value")
        expect(mocked(add_ints)(5,5)) to equal(10)
      end
    end
  end
end