#include "testsuite.h"

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
          expect(mock_for(add_ints)) to have been_called
        #else
          expect(mock_for(add_ints)) to not have been_called
        #endif
      end

      it("tracks the call parameters")
        mock(add_ints) and_return(3)
        #if LD_WRAP
          add_ints(2, 2);
          add_ints(2, 2);
        #else
          __wrap_add_ints(2, 2);
          __wrap_add_ints(2, 2);
        #endif
        expect(mock_for(add_ints)->calls->call_number) to equal(1)
        expect(mock_for(add_ints)->calls->next->call_number) to equal(2)
        expect(mock_for(add_ints)->calls->n_args) to equal(2)
        expect(mock_for(add_ints)) to have been called_with(2,2)
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

    context("parameters")
      when("a variety of parameter types are passed")
        mock(person_constructor) no_return
        it("asserts the mock was called")
          __wrap_person_constructor("Fry", 3000);
          expect(mock_for(person_constructor)) to have been called_with("Fry", 3000)
          expect(mock_for(person_constructor)) to not have been called_with("Fry", "3000")
        end
      end

      context("char")
        mock(test_char) no_return
        it("asserts the mock was called")
          __wrap_test_char('A');
          expect(mock_for(test_char)) to have been called_with('A')
        end
      end
    end

  end
end