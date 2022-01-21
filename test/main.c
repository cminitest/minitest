#include "testsuite.h"

#define EXPECTED_FAILURES 24

mt_mocks_initialize(
  mt_mock_parameter_handles(
    mt_mock_parameter_handle(ExpectExt*, expect_ext_value)
    mt_mock_parameter_handle(void**, expect_void_ptrptr_value)
  ),
  mt_mock_assert_parameters(
    mt_mock_assert_parameter(expect_ext_value, (mt_mock_expected.expect_ext_value->value == mt_mock_actual.expect_ext_value->value))
  )
)

int main() {
  minitest.run();

  int result = EXPECTED_FAILURES - minitest.failures;

  minitest.clear(&minitest);

  return result;
}