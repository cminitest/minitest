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
#define MT_UNIQUE_NAME( name ) MT_DEFINE_UNIQUE_NAME( name, __COUNTER__ )

#define MT_ATTR_SUPPORTED 1

//
// __attribute__ support
//
#if !defined(__GNUC__) && !defined(__GNUG__) && !defined(__clang__)
  #undef MT_ATTR_SUPPORTED
  #define MT_ATTR_SUPPORTED 0
  #define __attribute__(name) mt_unsported_##name##__COUNTER__
#endif

#if !defined(MT_MAX_FIXTURES)
  #define MT_MAX_FIXTURES 25
#endif

#define MT_STDIO 0x01
#define MT_XML 0x02

//#define do  {
#define end minitest.step_back(&minitest); }

//
// DESCRIBE blocks
//
#define MT_REGISTER_SUITE( suite, handle, TestName, ... ) \
  static void handle(MiniTest* mt); \
  static void __attribute__((constructor)) MT_CONSTRUCTOR_NAME(handle)(void) {\
    minitest.register_suite(&minitest, suite, handle); \
  } \
  static void handle(MiniTest* mt) { void* current_expect = NULL;

#define MT_DEFINE_SUITE( suite, handle, ... ) \
  MT_REGISTER_SUITE( suite, handle, MT_UNIQUE_NAME( MINITEST_ ), __VA_ARGS__ )
#define MT_SUITE( suite, handle, ... ) MT_DEFINE_SUITE( suite, handle, __VA_ARGS__ )

#if MT_ATTR_SUPPORTED
  #define describe( suite, handle, ... ) MT_SUITE( suite, handle, __VA_ARGS__ )
#else
  #define describe( handle, ... ) MT_SUITE( "Minitest Default", handle, __VA_ARGS__ )
#endif

//
// behavior blocks
//
#define MT_REGISTER_TEST_CASE( test_type, test_case, TestName, ... ) \
  minitest.register_block(test_type, &minitest, test_case); {
#define MT_DEFINE_TEST_CASE( test_type, test_case, ... ) \
  MT_REGISTER_TEST_CASE( test_type, test_case, MT_UNIQUE_NAME( MINITEST_ ), __VA_ARGS__ )
#define MT_TEST_CASE( test_case_type, testcase, ... ) MT_DEFINE_TEST_CASE( test_case_type, testcase, __VA_ARGS__ )

#define context( testcase, ... ) MT_TEST_CASE( CONTEXT_TYPE, testcase, __VA_ARGS__ )
#define it( testcase, ... ) MT_TEST_CASE( IT_TYPE, testcase, __VA_ARGS__ )
#define given( testcase, ... ) MT_TEST_CASE( GIVEN_TYPE, testcase, __VA_ARGS__ )
#define and( testcase, ... ) MT_TEST_CASE( AND_TYPE, testcase, __VA_ARGS__ )
#define when( testcase, ... ) MT_TEST_CASE( WHEN_TYPE, testcase, __VA_ARGS__ )

#define mt_fixture_before(id) static void __before_fixture_##id (void** subject)
#define mt_fixture_after(id) static void __after_fixture_##id (void** subject)
#define mt_define_fixture_type(fixture_type, id) mt_fixture_##fixture_type(id)
#define define_fixture(...) mt_define_fixture_type(__VA_ARGS__)

#define mt_set_fixture_type_name(t, id) __##t##_fixture_##id
#define mt_set_fixture_type_after(id) minitest.current->current_block->after = mt_set_fixture_type_name(after, id);
#define mt_set_fixture_type_before(id) minitest.current->current_block->before = mt_set_fixture_type_name(before, id);
#define mt_set_fixture_type(fixture_type, id) mt_set_fixture_type_##fixture_type(id)
#define set_fixture(...) mt_set_fixture_type(__VA_ARGS__)

#ifndef before
  #define before(id) set_fixture(before, id)
#endif

#ifndef after
  #define after(id) set_fixture(after, id)
#endif

#define subject(t) minitest.current->subject

#endif