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