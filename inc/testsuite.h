#ifndef __MINITEST_TESTSUITE_H__
#define __MINITEST_TESTSUITE_H__ 1

#include "minitest/setup.h"

typedef struct ExpectExtStruct {
  int value;
} ExpectExt;

int add_ints(int n1, int n2);
int add_three_ints(int n1, int n2, int n3);

void test_char(char n);
void test_short(short n);
void test_long(long n);
void test_double(double n);
void test_float(float n);
void test_void_ptr(void* n);
void test_char_ptr(char* n);
void test_size_t(size_t n);
void test_u_int(unsigned int n);
void test_u_short(unsigned short n);
void test_u_char(unsigned char n);
void test_int_array(int* n);
void test_short_array(short* n);
void test_long_array(long* n);
void test_double_array(double* n);
void test_float_array(float* n);

void person_constructor(char* name, short age);

mt_setup_expect_forwards(
  mt_expect_forward(extstruct, ExpectExt*)
  mt_expect_array_forward(extstructarr, ExpectExt*)
)

#define MT_EXPECT_EXTENSIONS mt_setup_expect_extensions( \
  mt_expect_extension(extstruct, ExpectExt*)             \
  mt_expect_extension(extstructarr, ExpectExt**)         \
)

mt_setup_mocks(
  mt_param_extensions(
    mt_mock_param(ExpectExt*, expect_ext_value)
    mt_mock_param(void**, expect_void_ptrptr_value)
  ),
  mt_setup_mock_forwards(
    mt_mock_forward(mt_returns,   int, add_ints, int n1, int n2)
    mt_mock_forward(mt_no_return, void, person_constructor,  char* name, short age)
    mt_mock_forward(mt_no_return, void, test_char,          char n)
    mt_mock_forward(mt_no_return, void, test_short,         short n)
    mt_mock_forward(mt_no_return, void, test_long,          long n)
    mt_mock_forward(mt_no_return, void, test_double,        double n)
    mt_mock_forward(mt_no_return, void, test_float,         float n)
    mt_mock_forward(mt_no_return, void, test_void_ptr,      void* n)
    mt_mock_forward(mt_no_return, void, test_char_ptr,      char* n)
    mt_mock_forward(mt_no_return, void, test_size_t,        size_t n)
    mt_mock_forward(mt_no_return, void, test_u_int,         unsigned int n)
    mt_mock_forward(mt_no_return, void, test_u_short,       unsigned short n)
    mt_mock_forward(mt_no_return, void, test_u_char,        unsigned char n)
    mt_mock_forward(mt_no_return, void, test_int_array,     int* n)
    mt_mock_forward(mt_no_return, void, test_short_array,   short* n)
    mt_mock_forward(mt_no_return, void, test_long_array,    long* n)
    mt_mock_forward(mt_no_return, void, test_double_array,  double* n)
    mt_mock_forward(mt_no_return, void, test_float_array,   float* n)
  )
)

#include "minitest/minitest.h"

#endif