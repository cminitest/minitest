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

mt_define_mock(add_ints, int, 2,
  mt_mock_arg_signature(int, int),
  mt_mock_arg_names(n1,n2),
  int n1, int n2
)

mt_define_mock(person_constructor, mt_void_type, 2,
  mt_mock_arg_signature(char*, short),
  mt_mock_arg_names(name,age),
  char* name, short age
)

/*
    mt_mock_forward(test_char, mt_void_type,         1, char n)
    mt_mock_forward(test_short, mt_void_type,        1, short n)
    mt_mock_forward(test_long, mt_void_type,         1, long n)
    mt_mock_forward(test_double, mt_void_type,       1, double n)
    mt_mock_forward(test_float, mt_void_type,        1, float n)
    mt_mock_forward(test_void_ptr, mt_void_type,     1, void* n)
    mt_mock_forward(test_char_ptr, mt_void_type,     1, char* n)
    mt_mock_forward(test_size_t, mt_void_type,       1, size_t n)
    mt_mock_forward(test_u_int, mt_void_type,        1, unsigned int n)
    mt_mock_forward(test_u_short, mt_void_type,      1, unsigned short n)
    mt_mock_forward(test_u_char, mt_void_type,       1, unsigned char n)
    mt_mock_forward(test_int_array, mt_void_type,    1, int n[])
    mt_mock_forward(test_short_array, mt_void_type,  1, short n[])
    mt_mock_forward(test_long_array, mt_void_type,   1, long n[])
    mt_mock_forward(test_double_array, mt_void_type, 1, double n[])
    mt_mock_forward(test_float_array, mt_void_type,  1, float n[])
*/

#undef MT_LD_WRAP
#define MT_LD_WRAP 2

mt_define_mock(test_char, mt_void_type, 1,
  mt_mock_arg_signature(char),
  mt_mock_arg_names(n),
  char n
)

#undef MT_LD_WRAP
#define MT_LD_WRAP 1