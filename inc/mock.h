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

#define mt_mock_param(type, attribute) type attribute;

#define mt_param_extensions(...) ( __VA_ARGS__ )

#define mt_mock_argtype_string(v) #v
#define mt_mock_function_args_0(...)   char* args[] = {}
#define mt_mock_function_args_1(n1)    char* args[] = { mt_mock_argtype_string(n1) }
#define mt_mock_function_args_2(n1,n2) char* args[] = { mt_mock_argtype_string(n1), mt_mock_argtype_string(n2) }
#define mt_mock_function_args_3(n1,n2,n3) char* args[] = { mt_mock_argtype_string(n1), mt_mock_argtype_string(n2), mt_mock_argtype_string(n3) }

#define mt_set_call_value_if(param, value, type, cast, key) \
  if(strcmp(value, type) == 0) {                     \
    param.data.key = va_arg(valist, cast);           \
    param.data_type = malloc(sizeof(type));          \
    strcpy(param.data_type, type);                   \
    call->params[i] = param;                         \
    continue;                                        \
  }                                                  \

#define mt_set_param_value_if(param, value, type, cast, key) \
  if(strcmp(value, type) == 0) {                     \
    param->data.key = va_arg(valist, cast);         \
    param->data_type = malloc(sizeof(type));          \
    strcpy(param->data_type, type);                   \
    params[i] = param;                              \
    continue;                                        \
  }                                                  \

#define mt_check_if_type(t1,t2,condition) if(strcmp(t1, t2) == 0 && (condition) ) { call_found = 1; break; }

#define mt_setup_mock_forwards(...) ( __VA_ARGS__ )

#define mt_mock_forward(function_name, return_type, argc, ...)     \
  return_type __real_##function_name(__VA_ARGS__);                 \
  return_type __wrap_##function_name(__VA_ARGS__);                 \
  MiniTestMock* __init_##function_name(MiniTestMockSuite *s);      \
                                                                   \
  typedef struct __##function_name##Struct {                 \
    return_type return_value;                                \
    return_type (*handle)(__VA_ARGS__);                      \
  } function_name##Struct;                                   \
                                                             \

// =======================================
//      Mock Structures
// =======================================

#define mt_setup_mocks(param_extensions, forwards)    \
  mt_splat_args forwards                    \
  typedef struct __MockParamStruct {        \
    char* data_type;                        \
    size_t array_size;                      \
    union {                                 \
      int int_value;                        \
      char char_value;                      \
      short short_value;                    \
      long long_value;                      \
      double double_value;                  \
      float float_value;                    \
      void* void_ptr_value;                 \
      char* char_ptr_value;                 \
      size_t size_t_value;                  \
      unsigned int u_int_value;             \
      unsigned short u_short_value;         \
      unsigned char u_char_value;           \
      int* int_array_value;                 \
      short* short_array_value;             \
      long* long_array_value;               \
      double* double_array_value;           \
      float* float_array_value;             \
      mt_splat_args param_extensions        \
    } data;                                 \
  } MockParam;                              \
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
    struct MiniTestMockStruct* next;        \
  } MiniTestMock;                           \
                                            \
  void __expect_mock(MiniTest*, MiniTestMock*, size_t, int, void*, size_t, void*, size_t, mt_expect_flags); \
  int __expect_mock_condition(MiniTestMock*, void*, mt_expect_flags );                                      \
  MockParam** __expect_create_mock_params(MiniTestMock*, int, ...);                                         \
  int __assert_params_equal(MiniTestMock*, MockParam**);                                                    \
  MiniTestMock* mt_find_node(MiniTestMockSuite*, char*);                                                    \

// =======================================
//      Mock Params and Assertions
// =======================================

#define mt_mocks_initialize()                                                                                       \
  MiniTestMock* mt_find_node(MiniTestMockSuite *s, char* function_name) {                                           \
    MiniTestMock* current_node = s->nodes;                                                                          \
    while(strcmp(current_node->function, function_name) != 0) {                                                     \
      current_node = current_node->next;                                                                            \
    }                                                                                                               \
    if (strcmp(current_node->function, function_name) != 0 ) {                                                      \
      current_node = NULL;                                                                                          \
    }                                                                                                               \
    return current_node;                                                                                            \
  }                                                                                                                 \
                                                                                                                    \
  mt_expect_handle(mock, MiniTestMock*, void*, void*,, __expect_mock_condition(actual, expected, flag), NULL, NONE) \
  int __expect_mock_condition(MiniTestMock* mock, void* condition, mt_expect_flags flag) {  \
    switch(flag) {                                                                          \
      case MT_EXPECT_BEEN_CALLED_FLAG:                                                      \
        return mock->call_count > 0;                                                        \
      case MT_EXPECT_CALLED_WITH_FLAG:                                                      \
        return __assert_params_equal(mock, ((MockParam**)condition));                       \
      default:                                                                              \
        return 0;                                                                           \
    }                                                                                       \
  }                                                                                         \
                                                                                            \
  int __assert_params_equal(MiniTestMock* mock, MockParam** params) {                       \
    MockCall* cc = mock->calls;                                                             \
    int call_found = 0;                                                                     \
    while(cc != NULL && !call_found) {                                                      \
      for(int i = 0; i < cc->n_args; i++) {                                                 \
        mt_check_if_type(cc->params[i].data_type, "int", cc->params[i].data.int_value == params[i]->data.int_value) \
      }                                                                                     \
      cc = cc->next;                                                                        \
    }                                                                                       \
    return call_found;                                                                      \
  }                                                                                         \
                                                                                            \
  MockParam** __expect_create_mock_params(MiniTestMock* mock, int argc, ...) {              \
    MockParam** params = malloc(sizeof(MockParam)*argc);                                    \
    va_list valist;                                                                         \
    va_start(valist, argc);                                                                 \
    for(int i = 0; i < argc; i++) {                                                         \
      params[i] = malloc(sizeof(MockParam));                                                \
      mt_set_param_value_if(params[i], mock->argt_list[i], "int", int, int_value)           \
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

#define mt_define_mock(function_name, return_type, argc, arg_types, mock_args, ...) \
                                                                                    \
  void __##function_name##register_mock_call(MiniTestMock* mock, int cn, int argcount, ...) {    \
    MockCall* call = malloc(sizeof(MockCall));                          \
    call->n_args = argc;                                                \
    call->call_number = cn;                                             \
    call->next = NULL;                                                  \
    va_list valist;                                                     \
    va_start(valist, argcount);                                         \
    for(int i = 0; i < argcount; i++) {                                 \
      MockParam param;                                                  \
      mt_set_call_value_if(param, mock->argt_list[i], "int", int, int_value)   \
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
        function_name##Struct* data = (function_name##Struct*)current_node->data; \
        if (current_node->loaded) {                                               \
          if(current_node->released) { return data->handle mock_args ; }          \
          current_node->call_count += 1;                                          \
          __##function_name##register_mock_call (current_node, current_node->call_count, argc, mt_splat_args mock_args ) ; \
          return data->return_value;                                              \
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
  void __mock_##function_name(MiniTestMockSuite *s, return_type return_value) {   \
    if(s->nodes == NULL) { __init_##function_name(s); }                           \
    MiniTestMock* current_node = mt_find_node(s, #function_name);                 \
    if (strcmp(current_node->function, #function_name)!=0) {                      \
      current_node = __init_##function_name(s);                                   \
    }                                                                             \
    function_name##Struct* data = (function_name##Struct*)current_node->data;     \
    data->return_value = return_value;                                            \
    current_node->loaded = 1;                                                     \
    current_node->released = 0;                                                   \
    current_node->call_count = 0;                                                 \
    current_node->calls = NULL;                                                   \
    current_node->last_call = NULL;                                               \
  }                                                                               \
                                                                                  \
  typedef return_type (*type_##function_name)(__VA_ARGS__);                       \
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

#define and_return(value) value);
#define mock(function_name) __mock_##function_name(&minitestmocks, 
#define mocked(function_name) __mocked_##function_name(&minitestmocks)
#define release_mock(function_name) __release_##function_name(&minitestmocks);
#define mock_total_calls(function_name) __n_calls_##function_name(&minitestmocks)
#define mock_for(function_name) __this_##function_name(&minitestmocks)

// =======================================
//      Structures, types, forwards
// =======================================
typedef struct MiniTestMockStruct MiniTestMock;

typedef struct MiniTestMockSuiteStruct {
  MiniTestMock *nodes;
} MiniTestMockSuite;

MiniTestMock* mt_find_node(MiniTestMockSuite *s, char* function_name);

extern MiniTestMockSuite minitestmocks;

#endif