#include "minitest.h"

describe("MiniTest") do

  context("assertions") do

    context("equal") do
      it("is truthy") do
        expect("string") to equal("string")
      end
    end

    context("not equal") do
      it("is truthy") do
        expect("Bender") to not equal("Fry")
      end
    end

    context("int") do
      when("a valid assertion is made") do
        it("is truthy") do
          expect(1) to equal(1)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made") do
        it("fails") do
          expect(1) to equal(0)
          
          if (expect_result == TEST_FAILURE) { expect_result = TEST_PASS; }
        end
      end
    end

    context("char") do
      when("a valid assertion is made") do
        it("is truthy") do
          expect('a') to equal('a')
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made") do
        it("fails") do
          expect('a') to equal('b')
          
          if (expect_result == TEST_FAILURE) { expect_result = TEST_PASS; }
        end
      end
    end

    context("short") do
      when("a valid assertion is made") do
        it("is truthy") do
          short x = 2;
          expect(x) to equal(x)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made") do
        it("fails") do
          short x = 3;
          expect(x) to equal(0)
          
          if (expect_result == TEST_FAILURE) { expect_result = TEST_PASS; }
        end
      end
    end

    context("long") do
      when("a valid assertion is made") do
        it("is truthy") do
          long x = 2;
          expect(x) to equal(x)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made") do
        it("fails") do
          long x = 3;
          expect(x) to equal(0)
          
          if (expect_result == TEST_FAILURE) { expect_result = TEST_PASS; }
        end
      end
    end

    context("double") do
      when("a valid assertion is made") do
        it("is truthy") do
          double x = 2.5;
          expect(x) to equal(x)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made") do
        it("fails") do
          double x = 3.3;
          expect(x) to equal(0)
          
          if (expect_result == TEST_FAILURE) { expect_result = TEST_PASS; }
        end
      end
    end

    context("float") do
      when("a valid assertion is made") do
        it("is truthy") do
          float x = 3.14159f;
          expect(x) to equal(x)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made") do
        it("fails") do
          float x = 3.14159f;
          expect(x) to equal(0)
          
          if (expect_result == TEST_FAILURE) { expect_result = TEST_PASS; }
        end
      end
    end

    context("pointers") do
      when("a valid assertion is made") do
        it("is truthy") do
          void *x = NULL;
          expect(x) to equal(x)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made") do
        it("fails") do
          void *x; void *n;
          expect(x) to equal(n)
          
          if (expect_result == TEST_FAILURE) { expect_result = TEST_PASS; }
        end
      end
    end

    context("char*") do
      when("a valid assertion is made") do
        it("is truthy") do
          char *s = "hello world";
          expect(s) to equal(s)
          expect(expect_result) to equal(TEST_PASS)
        end
      end

      when("an invalid assertion is made") do
        it("fails") do
          char *s = "hello world";
          expect(s) to equal("hello")
          if (expect_result == TEST_FAILURE) { expect_result = TEST_PASS; }
        end
      end
    end

  end // end assertions

end