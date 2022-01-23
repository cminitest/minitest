#ifndef __MINITEST_MOCKS_H__
#define __MINITEST_MOCKS_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "common.h"

#define mt_mock_arg_names(...) ( __VA_ARGS__ )
#define mt_mock_arg_signature(...) ( __VA_ARGS__ )

#define mt_real_fn_handle(...) mt_real_fn_definition(__VA_ARGS__)
#define mt_real_fn_definition(function_name, tf) mt_real_fn_definition_##tf(function_name)
#define mt_real_fn_definition_0(function_name) function_name
#define mt_real_fn_definition_1(function_name) __real_##function_name
#define mt_real_fn_definition_2(function_name) NULL

#define mt_mock_param(type, attribute) type attribute;

#define mt_param_extensions(...) ( __VA_ARGS__ )

#define mt_mock_argtype_string(v) #v
#define mt_mock_function_args_0(...)   char* args[] = {}
#define mt_mock_function_args_1(n1)    char* args[] = { mt_mock_argtype_string(n1) }
#define mt_mock_function_args_2(n1,n2) char* args[] = { mt_mock_argtype_string(n1), mt_mock_argtype_string(n2) }
#define mt_mock_function_args_3(n1,n2,n3) char* args[] = { mt_mock_argtype_string(n1), mt_mock_argtype_string(n2), mt_mock_argtype_string(n3) }

#define mt_setup_mock_forwards(...) ( __VA_ARGS__ )

#define mt_rt_arg(fn_type, return_type) mt_rt_arg_##fn_type(return_type)
#define mt_rt_arg_0(return_type)
#define mt_rt_arg_1(return_type) ,return_type

#define mt_rt_struct(fn_type, return_type) mt_rt_struct_##fn_type(return_type)
#define mt_rt_struct_0(return_type) void* return_value;
#define mt_rt_struct_1(return_type) return_type return_value;

#define mt_rt_return(fn_type) mt_rt_return_##fn_type
#define mt_rt_return_0 ;
#define mt_rt_return_1 data->return_value;

#define mt_rt_real_return(fn_type) mt_rt_real_return_##fn_type
#define mt_rt_real_return_0 
#define mt_rt_real_return_1 return

#define mt_rt_set_return(fn_type, return_value) mt_rt_set_return_##fn_type(return_value)
#define mt_rt_set_return_0(return_value)
#define mt_rt_set_return_1(return_value) data->return_value = return_value;

#define mt_mock_forward(rts, return_type, function_name, ...)        \
  return_type __real_##function_name(__VA_ARGS__);                   \
  return_type __wrap_##function_name(__VA_ARGS__);                   \
  MiniTestMock* __init_##function_name(MiniTestMockSuite*);          \
  void __mock_##function_name(MiniTestMockSuite* mt_rt_arg(rts,return_type));      \
  MiniTestMock* __this_##function_name(MiniTestMockSuite*);          \
  int __n_calls_##function_name(MiniTestMockSuite*);                 \
  void __release_##function_name(MiniTestMockSuite*);                \
  typedef return_type (*type_##function_name)(__VA_ARGS__);          \
  type_##function_name __mocked_##function_name(MiniTestMockSuite*); \
                                                                     \
  typedef struct __##function_name##Struct {                 \
    mt_rt_struct(rts, return_type)                           \
    return_type (*handle)(__VA_ARGS__);                      \
    return_type (*through_handle)(__VA_ARGS__);              \
  } function_name##Struct;                                   \
                                                             \

#define mt_mock_expected cc->params[i].data
#define mt_mock_actual   params[i]->data

#define mt_mock_default_assert(attribute) (mt_mock_expected.attribute == mt_mock_actual.attribute)
#define mt_mock_assert_parameters(...) ( __VA_ARGS__ )
#define mt_mock_assert_parameter(attribute, condition)                                  \
  if(strcmp(cc->params[i].data_type, params[i]->data_type) != 0) { n_found = 0; break; }\
  if(strcmp(cc->params[i].attribute_type, #attribute) == 0) {                           \
    if(condition) { n_found += 1; continue; } else { n_found = 0; break; }              \
  }                                                                                     \
  

#define mt_mock_parameter_handles(...) ( __VA_ARGS__ )
#define mt_mock_parameter_handle(type, cast_type, attribute) \
 if(strcmp(mock->argt_list[i], #type) == 0) {                \
    found = 1;                                               \
    param->data.attribute = (type)va_arg(valist, cast_type); \
    param->data_type = malloc(sizeof(#type));                \
    param->attribute_type = malloc(sizeof(#attribute));      \
    strcpy(param->data_type, #type);                         \
    strcpy(param->attribute_type, #attribute);               \
  }; if(found) { this_index = param; found = 0; continue; }; \

#define __mt_parameter_handles                              \
  mt_mock_parameter_handle(int,    int,    int_value)       \
  mt_mock_parameter_handle(char,   int,    char_value)      \
  mt_mock_parameter_handle(short,  int,    short_value)     \
  mt_mock_parameter_handle(long,   long,   long_value)      \
  mt_mock_parameter_handle(double, double, double_value)    \
  mt_mock_parameter_handle(float,  double, float_value)     \
  mt_mock_parameter_handle(void*,  void*,  void_ptr_value)  \
  mt_mock_parameter_handle(char*,  char*,  char_ptr_value)  \
  mt_mock_parameter_handle(size_t, size_t, size_t_value)    \
  mt_mock_parameter_handle(unsigned int,   unsigned int, u_int_value)        \
  mt_mock_parameter_handle(unsigned short, int,          u_short_value)      \
  mt_mock_parameter_handle(unsigned char,  int,          u_char_value)       \
  mt_mock_parameter_handle(int*,           int*,         int_array_value)    \
  mt_mock_parameter_handle(short*,         short*,       short_array_value)  \
  mt_mock_parameter_handle(long*,          long*,        long_array_value)   \
  mt_mock_parameter_handle(double*,        double*,      double_array_value) \
  mt_mock_parameter_handle(float*,         float*,       float_array_value)  \

//
// TODO: have user prepare array size
//
#define __mt_param_assert_array(attribute, type) \
  __assert_array_##type(mt_mock_expected.attribute, mt_mock_actual.attribute, 0, 0)

#define __mt_parameter_assertions                                                      \
  mt_mock_assert_parameter(int_value,          mt_mock_default_assert(int_value))      \
  mt_mock_assert_parameter(char_value,         mt_mock_default_assert(char_value))     \
  mt_mock_assert_parameter(short_value,        mt_mock_default_assert(short_value))    \
  mt_mock_assert_parameter(long_value,         mt_mock_default_assert(long_value))     \
  mt_mock_assert_parameter(double_value,       __double_equal(mt_mock_expected.double_value,mt_mock_actual.double_value,MT_EXPECT_EPSILON))   \
  mt_mock_assert_parameter(float_value,        __float_equal(mt_mock_expected.float_value,mt_mock_actual.float_value,MT_EXPECT_EPSILON))      \
  mt_mock_assert_parameter(void_ptr_value,     mt_mock_default_assert(void_ptr_value)) \
  mt_mock_assert_parameter(char_ptr_value,     (strcmp(mt_mock_expected.char_ptr_value, mt_mock_actual.char_ptr_value) == 0)) \
  mt_mock_assert_parameter(size_t_value,       mt_mock_default_assert(size_t_value))   \
  mt_mock_assert_parameter(u_int_value,        mt_mock_default_assert(u_int_value))    \
  mt_mock_assert_parameter(u_short_value,      mt_mock_default_assert(u_short_value))  \
  mt_mock_assert_parameter(u_char_value,       mt_mock_default_assert(u_char_value))   \
  mt_mock_assert_parameter(int_array_value,    __mt_param_assert_array(int_array_value, int))      \
  mt_mock_assert_parameter(short_array_value,  __mt_param_assert_array(short_array_value, short))  \
  mt_mock_assert_parameter(long_array_value,   __mt_param_assert_array(long_array_value, long))    \
  mt_mock_assert_parameter(double_array_value, __mt_param_assert_array(double_array_value, double))\
  mt_mock_assert_parameter(float_array_value,  __mt_param_assert_array(float_array_value, float))  \

// =======================================
//      Mock Structures
// =======================================

#define mt_setup_mocks(param_extensions, forwards)    \
  mt_splat_args forwards                    \
  typedef union __mt_uMockParam {           \
    int int_value;                          \
    char char_value;                        \
    short short_value;                      \
    long long_value;                        \
    double double_value;                    \
    float float_value;                      \
    void* void_ptr_value;                   \
    char* char_ptr_value;                   \
    size_t size_t_value;                    \
    unsigned int u_int_value;               \
    unsigned short u_short_value;           \
    unsigned char u_char_value;             \
    int* int_array_value;                   \
    short* short_array_value;               \
    long* long_array_value;                 \
    double* double_array_value;             \
    float* float_array_value;               \
    mt_splat_args param_extensions          \
  } mt_uMockParam;                          \
                                            \
  typedef struct __MockParamStruct {        \
    char* data_type;                        \
    size_t array_size;                      \
    char* attribute_type;                   \
    mt_uMockParam data;                     \
  } MockParam;                              \
                                            \
  typedef struct __MockSpyStruct {          \
    int called;                             \
    int calls;                              \
  } MockSpy;                                \
                                            \
  typedef struct __MockCallStruct {         \
    int call_number;                        \
    int n_args;                             \
    MockParam params[MT_MOCK_MAX_ARGS];     \
    struct __MockCallStruct* next;          \
  } MockCall;                               \
                                            \
  typedef struct MiniTestMockStruct {       \
    char* function;                         \
    void* data;                             \
    int loaded;                             \
    int released;                           \
    int call_count;                         \
    char*     argt_list[MT_MOCK_MAX_ARGS];  \
    MockCall* calls;                        \
    MockCall* last_call;                    \
    MockSpy spy;                            \
    struct MiniTestMockStruct* next;        \
  } MiniTestMock;                           \
                                            \
  void __expect_mock(MiniTest*, MiniTestMock*, size_t, int, void*, size_t, void*, size_t, mt_expect_flags); \
  int __expect_mock_condition(MiniTestMock*, void*, mt_expect_flags );                                      \
  MockParam** __expect_create_mock_params(MiniTestMock*, int, ...);                                         \
  int __assert_params_equal(MiniTestMock*, MockParam**);                                                    \
  MiniTestMock* mt_find_node(MiniTestMockSuite*, char*);                                                    \
  void __register_mock_call(MiniTestMock* mock, int cn, int argcount, ...);                                 \

// =======================================
//      Mock Params and Assertions
// =======================================

#define mt_mocks_initialize(user_defined_params, user_defined_assertions)                                           \
  MiniTestMock* mt_find_node(MiniTestMockSuite *s, char* function_name) {                                           \
    MiniTestMock* current_node = s->nodes;                                                                          \
    while(current_node != NULL && strcmp(current_node->function, function_name) != 0) {                             \
      current_node = current_node->next;                                                                            \
    }                                                                                                               \
    if (current_node == NULL || strcmp(current_node->function, function_name) != 0 ) {                              \
      return NULL;                                                                                                  \
    }                                                                                                               \
    return current_node;                                                                                            \
  }                                                                                                                 \
                                                                                                                    \
  void __register_mock_call(MiniTestMock* mock, int cn, int argcount, ...) {    \
    MockCall* call = malloc(sizeof(MockCall));                          \
    call->n_args = argcount;                                            \
    call->call_number = cn;                                             \
    call->next = NULL;                                                  \
    int found = 0;                                                      \
    va_list valist;                                                     \
    va_start(valist, argcount);                                         \
    for(int i = 0; i < argcount; i++) {                                 \
      MockParam* this_index = &(call->params[i]);                       \
      MockParam* param = &(call->params[i]);                            \
      __mt_parameter_handles                                            \
      mt_splat_args user_defined_params                                 \
    }                                                                   \
    va_end(valist);                                                     \
    if (mock->last_call == NULL) {                                      \
      mock->calls = call;                                               \
      mock->last_call = call;                                           \
    } else {                                                            \
      mock->last_call->next = call;                                     \
      mock->last_call = call;                                           \
    }                                                                   \
  }                                                                     \
                                                                        \
  mt_expect_handle(mock, MiniTestMock*, void*, void*,, __expect_mock_condition(actual, expected, flag), NULL, NONE) \
                                                                                            \
  int __expect_mock_condition(MiniTestMock* mock, void* condition, mt_expect_flags flag) {  \
    switch(flag) {                                                                          \
      case MT_EXPECT_BEEN_CALLED_FLAG:                                                      \
        return mock->call_count > 0;                                                        \
      case MT_EXPECT_CALLED_WITH_FLAG:                                                      \
        return __assert_params_equal(                                                       \
          mock, ((MockParam**)condition)                                                    \
        );                                                                                  \
      default:                                                                              \
        return 0;                                                                           \
    }                                                                                       \
  }                                                                                         \
                                                                                            \
  int __assert_params_equal(                                                                \
      MiniTestMock* mock, MockParam** params                                                \
  ){                                                                                        \
    MockCall* cc = mock->calls;                                                             \
    int found = 0;                                                                          \
    while(cc != NULL && !found) {                                                           \
      int n_found = 0;                                                                      \
      for(int i = 0; i < cc->n_args; i++) {                                                 \
        __mt_parameter_assertions                                                           \
        mt_splat_args user_defined_assertions                                               \
      }                                                                                     \
      if(n_found == cc->n_args) { found = 1; } else { n_found = 0; }                        \
      cc = cc->next;                                                                        \
    }                                                                                       \
    return found;                                                                           \
  }                                                                                         \
                                                                                            \
  MockParam** __expect_create_mock_params(MiniTestMock* mock, int argc, ...) {              \
    MockParam** params = malloc(sizeof(MockParam)*argc);                                    \
    va_list valist;                                                                         \
    va_start(valist, argc);                                                                 \
    int found = 0;                                                                          \
    for(int i = 0; i < argc; i++) {                                                         \
      params[i] = malloc(sizeof(MockParam));                                                \
      MockParam* param = params[i];                                                         \
      MockParam* this_index = params[i];                                                    \
      __mt_parameter_handles                                                                \
      mt_splat_args user_defined_params                                                     \
    }                                                                                       \
    va_end(valist);                                                                         \
    return params;                                                                          \
  }                                                                                         \
  
/*
  TODO: __mock_##function_name needs to free mock calls if not null
*/

// =======================================
//      Mock Definition
// =======================================

//rts, return_type, 

#define mt_define_mock(rts, return_type, function_name, argc, arg_types, mock_args, ...) \
                                                                        \
  MiniTestMock* __init_##function_name(MiniTestMockSuite *s) {          \
    MiniTestMock* node = malloc(sizeof(MiniTestMock));                  \
    node->next = NULL;                                                  \
    node->calls = NULL;                                                 \
    node->last_call = NULL;                                             \
                                                                        \
    mt_mock_function_args_##argc arg_types;                             \
                                                                        \
    int i;                                                              \
    for(i=0;i<argc;i++) {                                               \
      node->argt_list[i] = malloc(strlen(args[i])+1);                   \
      strcpy(node->argt_list[i], args[i]);                              \
    }                                                                   \
                                                                        \
    function_name##Struct* data = malloc(sizeof(function_name##Struct));\
    node->function = malloc(strlen(#function_name) + 1);                \
    strcpy(node->function, #function_name);                             \
                                                                        \
    data->handle = mt_real_fn_handle(function_name, MT_LD_WRAP);        \
    node->data = (void*)data;                                           \
    if (s->nodes == NULL) {                                             \
      s->nodes = node;                                                  \
    } else {                                                            \
      MiniTestMock* current_node = s->nodes;                            \
      while(current_node->next != NULL) {                               \
        current_node = current_node->next;                              \
      }                                                                 \
      current_node->next = node;                                        \
    }                                                                   \
    return node;                                                        \
  }                                                                     \
                                                                        \
  return_type __wrap_##function_name(__VA_ARGS__) {                     \
    function_name##Struct* data;                                        \
    if(minitestmocks.nodes == NULL) {                                   \
      printf(MT_FUNCTION_NO_RETURN_ERROR, #function_name);              \
      exit(-1);                                                         \
    } else {                                                            \
      MiniTestMock* current_node = minitestmocks.nodes;                 \
      while(strcmp(current_node->function, #function_name)!=0) {        \
        current_node = current_node->next;                              \
      }                                                                 \
      if (strcmp(current_node->function, #function_name)==0) {          \
        function_name##Struct* data = (function_name##Struct*)current_node->data;                         \
        if (current_node->loaded) {                                                                       \
          if(data->through_handle != NULL) {                                                              \
            current_node->spy.calls += 1;                                                                 \
            current_node->spy.called = 1;                                                                 \
            data->through_handle mock_args ;                                                              \
          }                                                                                               \
          if(current_node->released) { mt_rt_real_return(rts) data->handle mock_args ; }                  \
          current_node->call_count += 1;                                                                  \
          __register_mock_call (current_node, current_node->call_count, argc, mt_splat_args mock_args ) ; \
          return mt_rt_return(rts)                                                \
        } else {                                                                  \
          printf(MT_FUNCTION_NO_RETURN_ERROR, #function_name);                    \
          exit(-1);                                                               \
        }                                                                         \
      } else {                                                                    \
        printf(MT_FUNCTION_NO_RETURN_ERROR, #function_name);                      \
        exit(-1);                                                                 \
      }                                                                           \
    }                                                                             \
  }                                                                               \
                                                                                  \
  void __mock_##function_name(MiniTestMockSuite *s mt_rt_arg(rts, return_type return_value)) {   \
    if(s->nodes == NULL) { __init_##function_name(s); }                           \
    MiniTestMock* current_node = mt_find_node(s, #function_name);                 \
    if (current_node == NULL || strcmp(current_node->function, #function_name)!=0) { \
      current_node = __init_##function_name(s);                                   \
    }                                                                             \
    function_name##Struct* data = (function_name##Struct*)current_node->data;     \
    mt_rt_set_return(rts, return_value)                                           \
    current_node->loaded = 1;                                                     \
    current_node->released = 0;                                                   \
    current_node->call_count = 0;                                                 \
    current_node->calls = NULL;                                                   \
    current_node->last_call = NULL;                                               \
    data->through_handle = NULL;                                                  \
    current_node->spy.calls  = 0;                                                 \
    current_node->spy.called = 0;                                                 \
  }                                                                               \
                                                                                  \
  type_##function_name __mocked_##function_name(MiniTestMockSuite *s) {           \
    if(s->nodes == NULL) { __init_##function_name(s); }                           \
    MiniTestMock* current_node = mt_find_node(s, #function_name);                 \
    if (strcmp(current_node->function, #function_name)!=0) {                      \
      current_node = __init_##function_name(s);                                   \
    }                                                                             \
    function_name##Struct* data = (function_name##Struct*)current_node->data;     \
    return data->handle;                                                          \
  }                                                                               \
                                                                                  \
  void __release_##function_name(MiniTestMockSuite *s) {                          \
    if(s->nodes == NULL) { __init_##function_name(s); }                           \
    MiniTestMock* current_node = mt_find_node(s, #function_name);                 \
    if (strcmp(current_node->function, #function_name)!=0) {                      \
      current_node = __init_##function_name(s);                                   \
    }                                                                             \
    current_node->released = 1;                                                   \
  }                                                                               \
                                                                                  \
  int __n_calls_##function_name(MiniTestMockSuite *s) {                           \
    if(s->nodes == NULL) { __init_##function_name(s); }                           \
    MiniTestMock* current_node = mt_find_node(s, #function_name);                 \
    if (strcmp(current_node->function, #function_name)!=0) {                      \
      current_node = __init_##function_name(s);                                   \
    }                                                                             \
    return current_node->call_count;                                              \
  }                                                                               \
                                                                                  \
  MiniTestMock* __this_##function_name(MiniTestMockSuite *s) {                    \
    if(s->nodes == NULL) { __init_##function_name(s); }                           \
    MiniTestMock* current_node = mt_find_node(s, #function_name);                 \
    if (strcmp(current_node->function, #function_name)!=0) {                      \
      current_node = __init_##function_name(s);                                   \
    }                                                                             \
    return current_node;                                                          \
  }                                                                               \

// =======================================
//      Mock Helper Macros
// =======================================

#define no_return );
#define and_return(value) ,value);
#define mock(function_name) __mock_##function_name(&minitestmocks 
#define mocked(function_name) __mocked_##function_name(&minitestmocks)
#define release_mock(function_name) __release_##function_name(&minitestmocks);
#define mock_total_calls(function_name) __n_calls_##function_name(&minitestmocks)
#define mock_for(function_name) __this_##function_name(&minitestmocks)

#define spy_for(function_name) (__this_##function_name(&minitestmocks))->spy
#define spy_on(function_name) ((function_name##Struct*)((__this_##function_name(&minitestmocks))->data))
#define through(handle) -> through_handle = handle;

// =======================================
//      Structures, types, forwards
// =======================================

int __assert_array_int(int arr_1[], int arr_2[], size_t s1, size_t s2);
int __assert_array_short(short arr_1[], short arr_2[], size_t s1, size_t s2);
int __assert_array_long(long arr_1[], long arr_2[], size_t s1, size_t s2);
int __assert_array_double(double arr_1[], double arr_2[], size_t s1, size_t s2);
int __assert_array_float(float arr_1[], float arr_2[], size_t s1, size_t s2);
int __double_equal(double, double, double);
int __float_equal(float, float, float);

typedef struct __MockSpyStruct MockSpy;
typedef struct MiniTestMockStruct MiniTestMock;

typedef struct MiniTestMockSuiteStruct {
  MiniTestMock *nodes;
} MiniTestMockSuite;

MiniTestMock* mt_find_node(MiniTestMockSuite *s, char* function_name);

extern MiniTestMockSuite minitestmocks;

#endif