#ifndef __MINITEST_COMMON_H__
#define __MINITEST_COMMON_H__ 1

// =======================================
//         Constants / Settings
// =======================================

#ifndef MT_MAX_ASSERTION_BUFFER
#define MT_MAX_ASSERTION_BUFFER 0x400
#endif

#ifndef MT_EXPECT_EPSILON
#define MT_EXPECT_EPSILON 0.000001
#endif

#ifdef LD_WRAP
  #undef LD_WRAP
  #define LD_WRAP 1
#else
  #define LD_WRAP 0
#endif

#define MT_LD_WRAP LD_WRAP

#ifndef MT_MOCK_MAX_ARGS
  #define MT_MOCK_MAX_ARGS 9
#endif

#define MT_FUNCTION_NO_RETURN_ERROR "Function %s has not been initialized with a return value."

// =======================================
//               Macros
// =======================================

#define mt_splat_args(...) __VA_ARGS__

#define mt_expect_forward(suffix, type) \
  void __expect_##suffix(MiniTest *mt, type actual, size_t as, int negated, type expected, size_t es, type max_range, size_t ms, mt_expect_flags flag)

#define mt_expect_array_forward(suffix, type) \
  void __expect_##suffix(MiniTest *mt, type actual[], size_t as, int negated, type expected[], size_t es, type max_range[], size_t ms, mt_expect_flags flag)

// =======================================
//               Forwards
// =======================================

typedef struct MiniTestStruct MiniTest;
typedef struct MiniTestSuiteStruct MiniTestSuite;
typedef struct MiniTestBlockStruct MiniTestBlock;
typedef struct MiniTestBlockArrayStruct MiniTestBlockArray;

// =======================================
//               Types
// =======================================

typedef enum { 
  NONE,
  SINGLE,
  ARRAY,
  EXTENSION
} mt_format;

typedef enum { 
  MT_EXPECT_EQUAL_FLAG,
  MT_EXPECT_GT_FLAG,
  MT_EXPECT_LT_FLAG,
  MT_EXPECT_GTE_FLAG,
  MT_EXPECT_LTE_FLAG,
  MT_EXPECT_RANGE_FLAG,
  MT_EXPECT_BEEN_CALLED_FLAG,
  MT_EXPECT_CALLED_WITH_FLAG,
} mt_expect_flags;

#endif