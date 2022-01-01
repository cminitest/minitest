# Minitest [![MacOS](https://github.com/Vandise/minitest/actions/workflows/MacOS.yml/badge.svg)](https://github.com/Vandise/minitest/actions/workflows/MacOS.yml) [![Ubuntu](https://github.com/Vandise/minitest/actions/workflows/Ubuntu.yml/badge.svg)](https://github.com/Vandise/minitest/actions/workflows/Ubuntu.yml) [![Windows](https://github.com/Vandise/minitest/actions/workflows/Windows.yml/badge.svg)](https://github.com/Vandise/minitest/actions/workflows/Windows.yml)

A behavior-driven test library for C.

## Goals

- A small, behavior-driven, test library for C.
- No extensions to the C-library
- Extensible assertions

## Todo

- License
- Fault Capturing / jmps to next label (without fork)
- Documentation Improvements

## Example

Minitest has supporting unit tests written in Minitest. Further examples can be found <a href="https://github.com/Vandise/minitest/blob/master/test/assertions_test.c">here</a> and <a href="https://github.com/Vandise/minitest/blob/master/test/core_test.c">here</a>.

```c
#include "minitest/minitest.h"

describe("MiniTest", minitest_suite)
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

Minitest uses GNU autotools and make to compile and install the library.

### Clone this repository

```
$> git clone https://github.com/Vandise/minitest
```

### Generate the Makefile

```
$> autoconf
$> ./configure
```

### Build and install the library

```
$> make
```

### Run the test suite

```
$> ./bin/testsuite
```

## How do I use the library?

Minitest needs to be booted in the main() function of your test suite. The following is a minimal example to get started.

**If your compiler supports __attribute__((constructor)):**

```
// main.c
#include "minitest/minitest.h"

int add(int n1, int n2) {
  return n1 + n2;
}

describe("My Program", my_program_suite)
  context(".add")
    it("returns the sum of two numbers")
      expect(add(2,2)) to equal(4)
    end
  end
end

int main() {
  minitest.run();
  
  int failures = minitest.failures;
  
  minitest.clear(&minitest); // optional, frees memory and clears the test suite
  
  return failures > 0 ? 1 : 0;
}
```

**If your compiler does not support __attribute__((constructor)):**

```
// main.c
#include "minitest/minitest.h"

int add(int n1, int n2) {
  return n1 + n2;
}

describe(my_program_suite)
  context(".add")
    it("returns the sum of two numbers")
      expect(add(2,2)) to equal(4)
    end
  end
end

int main() {
  minitest.register_suite(&minitest, "My Program", my_program_suite);

  minitest.run();

  int failures = minitest.failures;
  
  minitest.clear(&minitest); // optional, frees memory and clears the test suite
  
  return failures > 0 ? 1 : 0;
}
```

Compilation:

```
$> gcc -o testsuite main.c -lminitest
```

## Constructs

### describe

Describe initializes a test suite. It describes a module, structure, and/or set of functions. A describe block is required before all other constructs.

The first argument is the description of the test suite, the second is the function handle/identifier that will be created.

```c
describe("My Test Suite", my_test_suite)
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

Assertion macros require C11 and above. The assertion library allows the expectation of something being equal, not equal, and greater/less than.

```c
expect("hello world") to equal("hello world")
expect("hello Bender") to not equal("hello Fry")

expect(NULL) to be_null
expect(0) to be_false
expect(1) to be_true

expect(1) to be greater_than(0)
expect(0) to be less_than(1)
expect(0) to be less_than_or_equal_to(0)
expect(0) to be greater_than_or_equal_to(0)

expect(5) to be in_range(0,10)

expect(mock_calls(add_ints)) to have been_called
expect(mock_calls(add_ints)) to not have been_called
```

### Assertion Support

- int, int[] (int*)
- char, char*
- short, short[] (short*)
- long, long[] (long*)
- double, double[] (double*)
- float, float[] (float*)
- void*
- size_t
- unsigned char
- unsigned short
- unsigned int
- unsigned long

## Mocking

Minitest supports mocking through alias symbols or compilation macros. For example, with GCC you can specify the `--wrap=` parameter for a function.

```
gcc -Wl,--wrap=add_ints -o main main.c
```

Mocking examples can be found <a href="https://github.com/Vandise/minitest/blob/master/test/mocks_test.c">here</a>.

### mt_mock_forwards(function_name, return_type, argument_type argument ...);

Defines the forward mocking functions for `function_name`.

### mt_define_mock(function_name, mt_mock_args, return_type, argument_type argument ...)

Defines the mocking structures and functions for `function_name`.

### Example

```c
#include "minitest/minitest.h"

int add_ints(int n1, int n2) {
  return n1 + n2;
}

// include in your test header
mt_mock_forwards(add_ints, int, int n1, int n2);

mt_define_mock(add_ints, mt_mock_args(n1,n2) int, int n1, int n2);

describe("Mocks", mocks)
  mock(add_ints) and_return(5)

  it("returns 2+2=5")
    #ifdef LD_WRAP
      expect(add_ints(2, 2)) to equal(5) // pass -D LD_WRAP if your linker supports --wrap
    #else
      expect(__wrap_add_ints(2, 2)) to equal(5) // or run the mocked function directly with a macro
    #endif
  end
end
```

### Getting the original function handle

The original function handle will be aliased to `__real_<function name>` when using `--wrap`. Minitest provides a macro to return the original function handle:

```c
mock(add_ints) and_return(5) // to demo that the mock is ignored

expect(mocked(add_ints)(5,5)) to equal(10)
``` 

## Releasing the mock

To release the mock and enable it to always call the original function handle, the `release_mock(function_name)` will point the wrapped function to the original function.

Calling `mock(function_name) and_return(value)` will reinitialize the mock.

### Example

```c
when("a mock is released")
  mock(add_ints) and_return(3)
  release_mock(add_ints)

  it("executes the original function")
    expect(add_ints(2, 2)) to equal(4)
  end

  when("the function is mocked again")
    mock(add_ints) and_return(5)
    it("executes the mock")
      expect(add_ints(2, 2)) to equal(5)
    end      
  end
end
```

## Extensions

Minitest can be extended to support custom data types. Minitest uses C11's _Generic handle to identify the type for expect statements. You can add your own types by defining `MT_EXPECT_EXT` before loading the Minitest header.

### Macros

Minitest provides the following macros to define your extension:

#### mt\_expect\_forward(function\_identifier, data\_type)

Creates the forward definition of the expect function.

##### Example

```c
mt_expect_forward(extstruct, ExpectExt*);
```

#### mt\_expect\_array\_forward(function\_identifier, data\_type)

Creates the forward definition of the expect function for an array.

##### Example

```c
mt_expect_array_forward(intarr, int);
```

#### mt\_expect\_ext(function\_identifier, data\_type, comparison, printf\_format)

Defines the expect function. Two variables are exposed in this context:

- data\_type actual
- data\_type expected

**comparison** can be any C expression or function call passing in the actual and expected variables.

**printf\_format** is any printf format to display if the expectation fails. You can pass `NULL` if you do not want to print any error message.

**NOTE:**

You must define a `__format_<function_identifier>(data_type value)` handler that returns the appropriate value associated with `printf_format`. If you do not want to print out any custom error messages, you can define a `void* __format_<function_identifier>(data_type value) { return NULL; }` handler.

##### Example

```c
int __format_extstruct(ExpectExt* extstruct) {
  return extstruct->value;
}

mt_expect_ext(extstruct, ExpectExt*, (actual->value == expected->value), "%i");
```

### Full Extension Example

```c
// testsuite.h
#ifndef __MINITEST_TESTSUITE_H__
#define __MINITEST_TESTSUITE_H__ 1

// define any structures and MT_EXPECT_EXT before loading minitest.h

typedef struct ExpectExtStruct {
  int value;
} ExpectExt;

#define MT_EXPECT_EXT \
  ExpectExt*: __expect_extstruct,

#include "minitest/minitest.h"

// create the forward expect function, matching the function identifier in MT_EXPECT_EXT
mt_expect_forward(extstruct, ExpectExt*);

#endif
```

```c
#include "testsuite.h"

// define the error formating function, returning a value appropriate for printf("%i")
int __format_extstruct(ExpectExt* extstruct) {
  return extstruct->value;
}

// define the __expect_extstruct function, comparing the value properties in the struct
mt_expect_ext(extstruct, ExpectExt*, (actual->value == expected->value), "%i");

describe("MiniTest", minitest_extensions)
  context("Extensions")
    ExpectExt subject = { .value = 1 };
    it("creates the expectation for the extension")
      ExpectExt comp = { .value = 1 };
      expect(&subject) to equal(&comp)
      comp.value = 2;
      expect(&subject) to not equal(&comp)
    end
  end
end
```