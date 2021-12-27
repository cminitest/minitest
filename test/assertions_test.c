#include "minitest.h"

describe("MiniTest")

  context("assertions")

    context("equal")
      it("is truthy")
        expect("string") to equal("string")
      end
    end

    context("not equal")
      it("is truthy")
        expect("Bender") to not equal("Fry")
      end
    end

    context("be_null")
      it("is truthy")
        expect(NULL) to be_null
      end
    end

    context("be_false")
      it("is truthy")
        expect(0) to be_false
      end
    end

    context("be_true")
      it("is truthy")
        expect(1) to be_true
      end
    end

    when("an invalid assertion is made")
      context("equal")
        it("fails")
          expect(1) to equal(0)
        end
      end

      context("not equal")
        it("fails")
          expect(0) to not equal(0)
        end
      end
    end

    context("int")
      when("a valid assertion is made")
        it("is truthy")
          expect(1) to equal(1)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made")
        it("fails")
          expect(1) to equal(0)
        end
      end
    end

    context("char")
      when("a valid assertion is made")
        it("is truthy")
          expect('a') to equal('a')
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made")
        it("fails")
          expect('a') to equal('b')
          
          
        end
      end
    end

    context("short")
      when("a valid assertion is made")
        it("is truthy")
          short x = 2;
          expect(x) to equal(x)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made")
        it("fails")
          short x = 3;
          expect(x) to equal(0)
          
          
        end
      end
    end

    context("long")
      when("a valid assertion is made")
        it("is truthy")
          long x = 2;
          expect(x) to equal(x)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made")
        it("fails")
          long x = 3;
          expect(x) to equal(0)
          
          
        end
      end
    end

    context("double")
      when("a valid assertion is made")
        it("is truthy")
         double x = 2.5;
          expect(x) to equal(x)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made")
        it("fails")
         double x = 3.3;
          expect(x) to equal(0)
          
          
        end
      end
    end

    context("float")
      when("a valid assertion is made")
        it("is truthy")
          float x = 3.14159f;
          expect(x) to equal(x)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made")
        it("fails")
          float x = 3.14159f;
          expect(x) to equal(0)
          
          
        end
      end
    end

    context("pointers")
      when("a valid assertion is made")
        it("is truthy")
          void *x = NULL;
          expect(x) to equal(x)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made")
        it("fails")
          void *x; void *n;
          expect(x) to equal(n)
          
          
        end
      end
    end

    context("char*")
      when("a valid assertion is made")
        it("is truthy")
          char *s = "hello world";
          expect(s) to equal(s)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made")
        it("fails")
          char *s = "hello world";
          expect(s) to equal("hello")
          
        end
      end
    end

  end // end assertions

end