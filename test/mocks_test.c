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

    when("a function is spied on")
      spy_on(add_ints) through(add_ints_spy)
      it("runs the spy function")
        __wrap_add_ints(2, 2);
        expect(spy_for(add_ints).called) to be_true
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

      context("short")
        mock(test_short) no_return
        it("asserts the mock was called")
          __wrap_test_short(10);
          expect(mock_for(test_short)) to have been called_with(10)
        end
      end

      context("long")
        mock(test_long) no_return
        it("asserts the mock was called")
          __wrap_test_long(8080);
          expect(mock_for(test_long)) to have been called_with(8080)
        end
      end

      context("double")
        mock(test_double) no_return
        it("asserts the mock was called")
          __wrap_test_double(10.77);
          expect(mock_for(test_double)) to have been called_with(10.77)
        end
      end

      context("float")
        mock(test_float) no_return
        it("asserts the mock was called")
          __wrap_test_float(10.77f);
          expect(mock_for(test_float)) to have been called_with(10.77f)
        end
      end

      context("void*")
        mock(test_void_ptr) no_return
        it("asserts the mock was called")
          __wrap_test_void_ptr(NULL);
          expect(mock_for(test_void_ptr)) to have been called_with(NULL)
        end
      end

      context("char*")
        mock(test_char_ptr) no_return
        it("asserts the mock was called")
          __wrap_test_char_ptr("Bender");
          expect(mock_for(test_char_ptr)) to have been called_with("Bender")
        end
      end

      context("size_t")
        mock(test_size_t) no_return
        it("asserts the mock was called")
          __wrap_test_size_t(sizeof(long));
          expect(mock_for(test_size_t)) to have been called_with(sizeof(long))
        end
      end

      context("unsigned int")
        mock(test_u_int) no_return
        unsigned int i = 3000;
        it("asserts the mock was called")
          __wrap_test_u_int(i);
          expect(mock_for(test_u_int)) to have been called_with(i)
        end
      end

      context("unsigned short")
        mock(test_u_short) no_return
        unsigned short i = 298;
        it("asserts the mock was called")
          __wrap_test_u_short(i);
          expect(mock_for(test_u_short)) to have been called_with(i)
        end
      end

      context("unsigned char")
        mock(test_u_char) no_return
        unsigned char i = 250;
        it("asserts the mock was called")
          __wrap_test_u_char(i);
          expect(mock_for(test_u_char)) to have been called_with(i)
        end
      end
  
      context("int[]")
        mock(test_int_array) no_return
        it("asserts the mock was called")
          int i[] = {1, 6, 2};
          int j[] = {6, 2, 1};
          __wrap_test_int_array(i);
          expect(mock_for(test_int_array)) to have been called_with(j)
        end

        it("asserts the mock was not called")
          int i[] = {1, 6, 2};
          int j[] = {6, 2, 0};
          __wrap_test_int_array(i);
          expect(mock_for(test_int_array)) to not have been called_with(j)
        end
      end
/*
      context("short[]")
        mock(test_short_array) no_return
        it("asserts the mock was called")
          short i[] = {1, 6, 2, 9, 4, 5};
          short j[] = {6, 2, 1, 9, 4, 5};
          printf("short :: %lu (%lu) \n", sizeof(i), sizeof(i)/sizeof(short));
          __wrap_test_short_array(i);
          expect(mock_for(test_short_array)) to have been called_with(j)
        end
      end
*/
    end
  end
end