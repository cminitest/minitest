# Minitest

A behavior-driven test library for C.

## Goals

- A small, behavior-driven, test library for C.
- No extensions to the C-library

### Todo

- Suites use gcc's `__attribute__((constructor))` to register a suite, this needs to be updated to ensure this library works without extensions to the C language.

## Example

Minitest has supporting unit tests written in Minitest. Further examples can be found <a href="https://github.com/Vandise/minitest/blob/master/test/assertions_test.c">here</a> and <a href="https://github.com/Vandise/minitest/blob/master/test/core_test.c">here</a>.

```c
#include "minitest.h"

describe("MiniTest")

  it("is defined")
    expect(&minitest) to equal(&minitest)
  end

  context(".register_block")
    when("a block has not had any it blocks defined")
      it("creates a new array with 1 element")
        minitest.register_block(IT_TYPE, &minitest, "it block test");
        expect(minitest.current->it_blocks.size) to equal(1);
      end
    end
  end
end
```

### Output

```
describe Minitest:
  ✔ it is defined
  context .register_block
    when a block has not had any it blocks defined
      ✔ it creates a new array with 1 element
```

## Installation

Under Development.

## How do I use the library?

### describe

Describe initializes a test suite. It describes a module, structure, and/or set of functions. A describe block is required before all other constructs.

```c
describe("My Test Suite")
  // any C code or test constructs here
end
```

### context

Context blocks establish the context in which you are testing.

```c
context(".greet")
  // any C code or test constructs here
end
```

### when / given

When and given blocks describe behavior under certain constraints.

```c
when("the user enters in an empty name")
  // any C code or test constructs here
end

given("the user enters in an empty name")
  // any C code or test constructs here
end
```

### and

And blocks further describe behavior under certain constraints.

```c
and("the user submits the form")
  // any C code or test constructs here
end
```

### it

It blocks assert the behavior of the scenario. They may be defined in any block.

```
it("returns 'Hello Bender!'")
  expect(greet("Bender")) to equal("Hello Bender!")
end
```

## Assertions

Assertion macros require C11 and above. The assertion library allows the expectation of something being equal, or not equal.

```c
expect("hello world") to equal("hello world")
expect("hello Bender") to not equal("hello Fry")
```

### Assertion Support

- int
- char
- short
- long
- double
- float
- void*
- char*
- size_t
- unsigned int

And more to come.
