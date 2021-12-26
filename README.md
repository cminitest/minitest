# Minitest

A behavior-driven test library for C.

## Goals

- A small, behavior-driven, test library for C.
- No extensions to the C-library

### Todo

- Suites use gcc's `__attribute__((constructor))` to register a suite, this needs to be updated to ensure this library works without extensions to the C language.

## Example

```c
#include "minitest.h"

describe("MiniTest") do

  it("is defined") do
    expect(&minitest) to equal(&minitest)
  end

  context(".register_block") do
    when("a block has not had any it blocks defined") do
      it("creates a new array with 1 element") do
        minitest.register_block(IT_TYPE, &minitest, "it block test");
        expect(minitest.current->it_blocks.size) to equal(1);
      end
    end
  end

  context("expect(int)") do
    given("an equal assertion") do
      it("is truthy") do
        expect(1) to equal(1)
      end
    end

    given("a not equal assertion") do
      it("is truthy") do
        expect(1) to not equal(0)
      end
    end

    given("the assertion is invalid") do
      it("is false") do
        expect(0) to not equal(0)
      end
    end
  end
end
```