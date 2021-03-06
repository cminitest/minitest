#ifndef __MINITEST_AUTOGENERATED_H__
#define __MINITEST_AUTOGENERATED_H__ 1

//
// This file was autogenerated. Do not modify this file.
//

#define mt_sizeof_va_args(...) mt_sizeof_va_args_definition(__VA_ARGS__)
#define mt_sizeof_va_args_definition(n, ...) mt_sizeof_va_args_##n(__VA_ARGS__)
#define mt_mock_argtype_string(v) #v
#define mt_mock_function_args_0(...)   char* args[] = {}
#define mt_va_nargs(...) mt_va_nargs_definition(__VA_ARGS__, 12,11,10,9,8,7,6,5,4,3,2,1)
#define mt_va_nargs_definition(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12, N, ...) N
#define mt_spy_args(...) ( mt_spy_args_definition(__VA_ARGS__) )
#define mt_spy_args_definition(n, ...) mt_spy_args_##n(__VA_ARGS__)
#define mt_spy_arg_ptrs(...) ( mt_spy_arg_ptrs_(mt_va_nargs(__VA_ARGS__), __VA_ARGS__) )
#define mt_spy_arg_ptrs_(...)  mt_spy_arg_ptrs_definition(__VA_ARGS__)
#define mt_spy_arg_ptrs_definition(n, ...) mt_spy_arg_ptrs_##n(__VA_ARGS__)
#define mt_sizeof_va_args_1(n1) (size_t[]){sizeof(n1)}
#define mt_mock_function_args_1(n1) char* args[] = { mt_mock_argtype_string(n1) }
#define mt_spy_args_1(n1) n1*
#define mt_spy_arg_ptrs_1(n1) &n1
#define mt_sizeof_va_args_2(n1,n2) (size_t[]){sizeof(n1),sizeof(n2)}
#define mt_mock_function_args_2(n1,n2) char* args[] = { mt_mock_argtype_string(n1),mt_mock_argtype_string(n2) }
#define mt_spy_args_2(n1,n2) n1*,n2*
#define mt_spy_arg_ptrs_2(n1,n2) &n1,&n2
#define mt_sizeof_va_args_3(n1,n2,n3) (size_t[]){sizeof(n1),sizeof(n2),sizeof(n3)}
#define mt_mock_function_args_3(n1,n2,n3) char* args[] = { mt_mock_argtype_string(n1),mt_mock_argtype_string(n2),mt_mock_argtype_string(n3) }
#define mt_spy_args_3(n1,n2,n3) n1*,n2*,n3*
#define mt_spy_arg_ptrs_3(n1,n2,n3) &n1,&n2,&n3
#define mt_sizeof_va_args_4(n1,n2,n3,n4) (size_t[]){sizeof(n1),sizeof(n2),sizeof(n3),sizeof(n4)}
#define mt_mock_function_args_4(n1,n2,n3,n4) char* args[] = { mt_mock_argtype_string(n1),mt_mock_argtype_string(n2),mt_mock_argtype_string(n3),mt_mock_argtype_string(n4) }
#define mt_spy_args_4(n1,n2,n3,n4) n1*,n2*,n3*,n4*
#define mt_spy_arg_ptrs_4(n1,n2,n3,n4) &n1,&n2,&n3,&n4
#define mt_sizeof_va_args_5(n1,n2,n3,n4,n5) (size_t[]){sizeof(n1),sizeof(n2),sizeof(n3),sizeof(n4),sizeof(n5)}
#define mt_mock_function_args_5(n1,n2,n3,n4,n5) char* args[] = { mt_mock_argtype_string(n1),mt_mock_argtype_string(n2),mt_mock_argtype_string(n3),mt_mock_argtype_string(n4),mt_mock_argtype_string(n5) }
#define mt_spy_args_5(n1,n2,n3,n4,n5) n1*,n2*,n3*,n4*,n5*
#define mt_spy_arg_ptrs_5(n1,n2,n3,n4,n5) &n1,&n2,&n3,&n4,&n5
#define mt_sizeof_va_args_6(n1,n2,n3,n4,n5,n6) (size_t[]){sizeof(n1),sizeof(n2),sizeof(n3),sizeof(n4),sizeof(n5),sizeof(n6)}
#define mt_mock_function_args_6(n1,n2,n3,n4,n5,n6) char* args[] = { mt_mock_argtype_string(n1),mt_mock_argtype_string(n2),mt_mock_argtype_string(n3),mt_mock_argtype_string(n4),mt_mock_argtype_string(n5),mt_mock_argtype_string(n6) }
#define mt_spy_args_6(n1,n2,n3,n4,n5,n6) n1*,n2*,n3*,n4*,n5*,n6*
#define mt_spy_arg_ptrs_6(n1,n2,n3,n4,n5,n6) &n1,&n2,&n3,&n4,&n5,&n6
#define mt_sizeof_va_args_7(n1,n2,n3,n4,n5,n6,n7) (size_t[]){sizeof(n1),sizeof(n2),sizeof(n3),sizeof(n4),sizeof(n5),sizeof(n6),sizeof(n7)}
#define mt_mock_function_args_7(n1,n2,n3,n4,n5,n6,n7) char* args[] = { mt_mock_argtype_string(n1),mt_mock_argtype_string(n2),mt_mock_argtype_string(n3),mt_mock_argtype_string(n4),mt_mock_argtype_string(n5),mt_mock_argtype_string(n6),mt_mock_argtype_string(n7) }
#define mt_spy_args_7(n1,n2,n3,n4,n5,n6,n7) n1*,n2*,n3*,n4*,n5*,n6*,n7*
#define mt_spy_arg_ptrs_7(n1,n2,n3,n4,n5,n6,n7) &n1,&n2,&n3,&n4,&n5,&n6,&n7
#define mt_sizeof_va_args_8(n1,n2,n3,n4,n5,n6,n7,n8) (size_t[]){sizeof(n1),sizeof(n2),sizeof(n3),sizeof(n4),sizeof(n5),sizeof(n6),sizeof(n7),sizeof(n8)}
#define mt_mock_function_args_8(n1,n2,n3,n4,n5,n6,n7,n8) char* args[] = { mt_mock_argtype_string(n1),mt_mock_argtype_string(n2),mt_mock_argtype_string(n3),mt_mock_argtype_string(n4),mt_mock_argtype_string(n5),mt_mock_argtype_string(n6),mt_mock_argtype_string(n7),mt_mock_argtype_string(n8) }
#define mt_spy_args_8(n1,n2,n3,n4,n5,n6,n7,n8) n1*,n2*,n3*,n4*,n5*,n6*,n7*,n8*
#define mt_spy_arg_ptrs_8(n1,n2,n3,n4,n5,n6,n7,n8) &n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8
#define mt_sizeof_va_args_9(n1,n2,n3,n4,n5,n6,n7,n8,n9) (size_t[]){sizeof(n1),sizeof(n2),sizeof(n3),sizeof(n4),sizeof(n5),sizeof(n6),sizeof(n7),sizeof(n8),sizeof(n9)}
#define mt_mock_function_args_9(n1,n2,n3,n4,n5,n6,n7,n8,n9) char* args[] = { mt_mock_argtype_string(n1),mt_mock_argtype_string(n2),mt_mock_argtype_string(n3),mt_mock_argtype_string(n4),mt_mock_argtype_string(n5),mt_mock_argtype_string(n6),mt_mock_argtype_string(n7),mt_mock_argtype_string(n8),mt_mock_argtype_string(n9) }
#define mt_spy_args_9(n1,n2,n3,n4,n5,n6,n7,n8,n9) n1*,n2*,n3*,n4*,n5*,n6*,n7*,n8*,n9*
#define mt_spy_arg_ptrs_9(n1,n2,n3,n4,n5,n6,n7,n8,n9) &n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8,&n9
#define mt_sizeof_va_args_10(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10) (size_t[]){sizeof(n1),sizeof(n2),sizeof(n3),sizeof(n4),sizeof(n5),sizeof(n6),sizeof(n7),sizeof(n8),sizeof(n9),sizeof(n10)}
#define mt_mock_function_args_10(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10) char* args[] = { mt_mock_argtype_string(n1),mt_mock_argtype_string(n2),mt_mock_argtype_string(n3),mt_mock_argtype_string(n4),mt_mock_argtype_string(n5),mt_mock_argtype_string(n6),mt_mock_argtype_string(n7),mt_mock_argtype_string(n8),mt_mock_argtype_string(n9),mt_mock_argtype_string(n10) }
#define mt_spy_args_10(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10) n1*,n2*,n3*,n4*,n5*,n6*,n7*,n8*,n9*,n10*
#define mt_spy_arg_ptrs_10(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10) &n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8,&n9,&n10
#define mt_sizeof_va_args_11(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11) (size_t[]){sizeof(n1),sizeof(n2),sizeof(n3),sizeof(n4),sizeof(n5),sizeof(n6),sizeof(n7),sizeof(n8),sizeof(n9),sizeof(n10),sizeof(n11)}
#define mt_mock_function_args_11(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11) char* args[] = { mt_mock_argtype_string(n1),mt_mock_argtype_string(n2),mt_mock_argtype_string(n3),mt_mock_argtype_string(n4),mt_mock_argtype_string(n5),mt_mock_argtype_string(n6),mt_mock_argtype_string(n7),mt_mock_argtype_string(n8),mt_mock_argtype_string(n9),mt_mock_argtype_string(n10),mt_mock_argtype_string(n11) }
#define mt_spy_args_11(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11) n1*,n2*,n3*,n4*,n5*,n6*,n7*,n8*,n9*,n10*,n11*
#define mt_spy_arg_ptrs_11(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11) &n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8,&n9,&n10,&n11
#define mt_sizeof_va_args_12(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12) (size_t[]){sizeof(n1),sizeof(n2),sizeof(n3),sizeof(n4),sizeof(n5),sizeof(n6),sizeof(n7),sizeof(n8),sizeof(n9),sizeof(n10),sizeof(n11),sizeof(n12)}
#define mt_mock_function_args_12(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12) char* args[] = { mt_mock_argtype_string(n1),mt_mock_argtype_string(n2),mt_mock_argtype_string(n3),mt_mock_argtype_string(n4),mt_mock_argtype_string(n5),mt_mock_argtype_string(n6),mt_mock_argtype_string(n7),mt_mock_argtype_string(n8),mt_mock_argtype_string(n9),mt_mock_argtype_string(n10),mt_mock_argtype_string(n11),mt_mock_argtype_string(n12) }
#define mt_spy_args_12(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12) n1*,n2*,n3*,n4*,n5*,n6*,n7*,n8*,n9*,n10*,n11*,n12*
#define mt_spy_arg_ptrs_12(n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11,n12) &n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8,&n9,&n10,&n11,&n12
#endif
