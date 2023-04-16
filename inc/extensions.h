#ifndef __MINITEST_EXTENSIONS_H__
#define __MINITEST_EXTENSIONS_H__ 1

#include "minitest/common.h"

#define mt_setup_expect_forwards(...) mt_splat_args ( __VA_ARGS__ )
#define mt_setup_expect_extensions(...) mt_splat_args ( __VA_ARGS__ )
#define mt_expect_extension(symbol, datatype)  datatype: __expect_##symbol,

#endif