#ifndef __MINITEST_MACROS_H__
#define __MINITEST_MACROS_H__ 1

#define FAILURE_BULLET      "✖"
#define SUCCESS_BULLET      "✔"
#define PENDING_BULLET      "•"

#define TEST_FAILURE  0
#define TEST_PASS     1
#define TEST_PENDING -1

#define CONSOLE_DEFAULT "\033[0m"
#define CONSOLE_YELLOW  "\033[1;33m"
#define CONSOLE_CYAN    "\033[0;36m"
#define CONSOLE_GREEN   "\033[0;32m"
#define CONSOLE_RED     "\033[0;31m"

#define ROOT_TYPE 0x00
#define DESCRIBE_TYPE 0x01
#define IT_TYPE 0x02
#define CONTEXT_TYPE 0x03
#define GIVEN_TYPE 0x04
#define AND_TYPE 0x05
#define WHEN_TYPE 0x06

#define MT_TO_STRING( str ) #str
#define MT_CONSTRUCTOR_NAME( TestName ) __construct_ ## TestName
#define MT_CREATE_UNIQUE_NAME( name, line ) name##line
#define MT_DEFINE_UNIQUE_NAME( name, line ) MT_CREATE_UNIQUE_NAME( name, line )
#define MT_UNIQUE_NAME( name ) MT_DEFINE_UNIQUE_NAME( name, __LINE__ )

#define do  {
#define end minitest.step_back(&minitest); }

//
// DESCRIBE blocks
//
#define MT_REGISTER_SUITE( suite, TestName, ... ) \
  static void TestName(void); \
  static void __attribute__((constructor)) MT_CONSTRUCTOR_NAME(TestName)(void) {\
    minitest.register_suite(&minitest, suite, TestName); \
  } \
  static void TestName(void)

#define MT_DEFINE_SUITE( suite, ... ) \
  MT_REGISTER_SUITE( suite, MT_UNIQUE_NAME( MINITEST_ ), __VA_ARGS__ )
#define MT_SUITE( suite, ... ) MT_DEFINE_SUITE( suite, __VA_ARGS__ )

#define describe( suite, ... ) MT_SUITE( suite, __VA_ARGS__ )

//
// behavior blocks
//
#define MT_REGISTER_TEST_CASE( test_type, test_case, TestName, ... ) \
  minitest.register_block(test_type, &minitest, test_case);
#define MT_DEFINE_TEST_CASE( test_type, test_case, ... ) \
  MT_REGISTER_TEST_CASE( test_type, test_case, MT_UNIQUE_NAME( MINITEST_ ), __VA_ARGS__ )
#define MT_TEST_CASE( test_case_type, testcase, ... ) MT_DEFINE_TEST_CASE( test_case_type, testcase, __VA_ARGS__ )

#define context( testcase, ... ) MT_TEST_CASE( CONTEXT_TYPE, testcase, __VA_ARGS__ )
#define it( testcase, ... ) MT_TEST_CASE( IT_TYPE, testcase, __VA_ARGS__ )
#define given( testcase, ... ) MT_TEST_CASE( GIVEN_TYPE, testcase, __VA_ARGS__ )
#define and( testcase, ... ) MT_TEST_CASE( AND_TYPE, testcase, __VA_ARGS__ )
#define when( testcase, ... ) MT_TEST_CASE( WHEN_TYPE, testcase, __VA_ARGS__ )

#endif