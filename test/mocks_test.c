#include "testsuite.h"

mt_define_mock(add_ints, int, 2,
  mt_mock_arg_signature(int, int),
  mt_mock_arg_names(n1,n2),
  int n1, int n2
);

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

      it("registers the call")
        mock(add_ints) and_return(3)
        #if LD_WRAP
          add_ints(2, 2);
          expect(mock_calls(add_ints)) to have been_called
        #else
          expect(mock_calls(add_ints)) to not have been_called
        #endif
      end
    end

    when("the original mocked function is retrieved")
      it("returns the original value")
        expect(mocked(add_ints)(5,5)) to equal(10)
      end
    end

    when("a mock is released")
      mock(add_ints) and_return(3)
      release_mock(add_ints)

      it("executes the original function")
        #if LD_WRAP
          expect(add_ints(2, 2)) to equal(4)
        #else
          expect(__wrap_add_ints(2, 2)) to equal(4)
        #endif
      end

      when("the function is mocked again")
        mock(add_ints) and_return(5)
        it("executes the mock")
          #if LD_WRAP
            expect(add_ints(2, 2)) to equal(5)
          #else
            expect(__wrap_add_ints(2, 2)) to equal(5)
          #endif
        end      
      end
    end
  end
end