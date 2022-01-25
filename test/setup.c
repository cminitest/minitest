#include "testsuite.h"

mt_mocks_initialize(
  mt_mock_parameter_handles(
    mt_mock_parameter_handle(ExpectExt*, ExpectExt*, expect_ext_value)
    mt_mock_parameter_handle(void**, void**, expect_void_ptrptr_value)
  ),
  mt_mock_assert_parameters(
    mt_mock_assert_parameter(expect_ext_value, (mt_mock_expected.expect_ext_value->value == mt_mock_actual.expect_ext_value->value))
  )
)

int add_ints_spy(int n1, int n2) {
  printf("add_ints_spy: <n1: %d> , <n2: %d>\n", n1, n2);
  return 0;
}

mt_define_mock(mt_returns, int, add_ints, 2,
  mt_mock_arg_signature(int, int),
  mt_mock_arg_names(n1,n2),
  int n1, int n2
)

mt_define_mock(mt_no_return, void, person_constructor, 2,
  mt_mock_arg_signature(char*, short),
  mt_mock_arg_names(name,age),
  char* name, short age
)

#undef  MT_LD_WRAP
#define MT_LD_WRAP mt_mock_wrap_null

mt_define_mock(mt_no_return, void, test_char, 1,
  mt_mock_arg_signature(char),
  mt_mock_arg_names(n),
  char n
)

mt_define_mock(mt_no_return, void, test_short, 1,
  mt_mock_arg_signature(short),
  mt_mock_arg_names(n),
  short n
)

mt_define_mock(mt_no_return, void, test_long, 1,
  mt_mock_arg_signature(long),
  mt_mock_arg_names(n),
  long n
)

mt_define_mock(mt_no_return, void, test_double, 1,
  mt_mock_arg_signature(double),
  mt_mock_arg_names(n),
  double n
)

mt_define_mock(mt_no_return, void, test_float, 1,
  mt_mock_arg_signature(float),
  mt_mock_arg_names(n),
  float n
)

mt_define_mock(mt_no_return, void, test_void_ptr, 1,
  mt_mock_arg_signature(void*),
  mt_mock_arg_names(n),
  void* n
)

mt_define_mock(mt_no_return, void, test_char_ptr, 1,
  mt_mock_arg_signature(char*),
  mt_mock_arg_names(n),
  char* n
)

mt_define_mock(mt_no_return, void, test_size_t, 1,
  mt_mock_arg_signature(size_t),
  mt_mock_arg_names(n),
  size_t n
)

mt_define_mock(mt_no_return, void, test_u_int, 1,
  mt_mock_arg_signature(unsigned int),
  mt_mock_arg_names(n),
  unsigned int n
)

mt_define_mock(mt_no_return, void, test_u_short, 1,
  mt_mock_arg_signature(unsigned short),
  mt_mock_arg_names(n),
  unsigned short n
)

mt_define_mock(mt_no_return, void, test_u_char, 1,
  mt_mock_arg_signature(unsigned char),
  mt_mock_arg_names(n),
  unsigned char n
)

mt_define_mock(mt_no_return, void, test_int_array, 1,
  mt_mock_arg_signature(int*),
  mt_mock_arg_names(n),
  int* n
)

/*

mt_define_mock(mt_no_return, void, test_int_array, 1,
  mt_mock_arg_signature(int*),
  mt_mock_arg_names(n),
  int* n
)

mt_define_mock(mt_no_return, void, test_short_array, 1,
  mt_mock_arg_signature(short*),
  mt_mock_arg_names(n),
  short* n
)

    mt_mock_forward(mt_no_return, void, test_short_array,  1, short n[])
    mt_mock_forward(mt_no_return, void, test_long_array,   1, long n[])
    mt_mock_forward(mt_no_return, void, test_double_array, 1, double n[])
    mt_mock_forward(mt_no_return, void, test_float_array,  1, float n[])
*/


#undef  MT_LD_WRAP
#define MT_LD_WRAP mt_mock_wrap_real