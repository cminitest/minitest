#ifndef __MINITEST_MOCKS_H__
#define __MINITEST_MOCKS_H__ 1

#ifdef LD_WRAP
  #undef LD_WRAP
  #define LD_WRAP 1
#else
  #define LD_WRAP 0
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct MiniTestMockStruct {
  char* function;
  void* data;

  struct MiniTestMockStruct* next;
} MiniTestMock;

typedef struct MiniTestMockSuiteStruct {
  MiniTestMock *nodes;
} MiniTestMockSuite;

MiniTestMock* mt_find_node(MiniTestMockSuite *s, char* function_name);

#define MT_LD_WRAP LD_WRAP

#define MT_FUNCTION_NO_RETURN_ERROR "Function %s has not been initialized with a return value."

#define mt_mock_args(...) ( __VA_ARGS__ )

#define mt_real_fn_handle(...) mt_real_fn_definition(__VA_ARGS__)
#define mt_real_fn_definition(function_name, tf) mt_real_fn_definition_##tf(function_name)
#define mt_real_fn_definition_0(function_name) function_name
#define mt_real_fn_definition_1(function_name) __real_##function_name

#define mt_mock_param(type, attribute) type attribute;

#ifndef MT_MOCK_PARAM_VALUES
#define MT_MOCK_PARAM_VALUES
#endif

typedef struct __MockParamStruct { 
  char* data_type; 
  size_t array_size; 
  union { 
    int int_value; 
    char char_value; 
    short short_value; 
    long long_value; 
    double double_value; 
    float float_value; 
    void* void_ptr_value; 
    char* char_ptr_value; 
    size_t size_t_value; 
    unsigned int u_int_value; 
    unsigned short u_short_value; 
    unsigned char u_char_value; 
    int* int_array_value; 
    short* short_array_value; 
    long* long_array_value; 
    double* double_array_value; 
    float* float_array_value; 
    MT_MOCK_PARAM_VALUES 
  } data; 
} MockParam;

#define mt_mock_forwards(function_name, return_type, argc, ...)    \
  return_type __real_##function_name(__VA_ARGS__);                 \
  return_type __wrap_##function_name(__VA_ARGS__);                 \
  MiniTestMock* __init_##function_name(MiniTestMockSuite *s);      \
                                                                   \
  typedef struct __##function_name##CallStruct {                   \
    int call_number;                                               \
    MockParam params[argc];                                        \
    struct __##function_name##CallStruct *next;                    \
  } function_name##CallStruct;                                     \
                                                             \
  typedef struct __##function_name##Struct {                 \
    int loaded;                                              \
    int released;                                            \
    int call_count;                                          \
    function_name##CallStruct calls;                         \
    return_type return_value;                                \
    return_type (*handle)(__VA_ARGS__);                      \
  } function_name##Struct;                                   \
                                                             \

#define mt_define_mock(function_name, mock_args, return_type, ...)      \
  void __register_mock_call_args(function_name##Struct* mock, ...) {    \
  }                                                                     \
                                                                        \
  MiniTestMock* __init_##function_name(MiniTestMockSuite *s) {          \
    MiniTestMock* node = malloc(sizeof(MiniTestMock));                  \
    node->next = NULL;                                                  \
                                                                        \
    function_name##Struct* data = malloc(sizeof(function_name##Struct));\
    node->function = malloc(strlen(#function_name) + 1);                \
    strcpy(node->function, #function_name);                             \
    data->loaded = 0;                                                   \
    data->released = 0;                                                 \
    data->call_count = 0;                                               \
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
        if (data->loaded) {                                                       \
          if(data->released) { return data->handle mock_args ; }                  \
          data->call_count += 1;                                                  \
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
    data->loaded = 1;                                                             \
    data->released = 0;                                                           \
    data->call_count = 0;                                                         \
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
    function_name##Struct* data = (function_name##Struct*)current_node->data;     \
    data->released = 1;                                                           \
  }                                                                               \
                                                                                  \
  int __calls_##function_name(MiniTestMockSuite *s) {                             \
    if(s->nodes == NULL) { __init_##function_name(s); }                           \
    MiniTestMock* current_node = mt_find_node(s, #function_name);                 \
    if (strcmp(current_node->function, #function_name)!=0) {                      \
      current_node = __init_##function_name(s);                                   \
    }                                                                             \
    function_name##Struct* data = (function_name##Struct*)current_node->data;     \
    return data->call_count;                                                      \
  }                                                                               \

#define and_return(value) value);
#define mock(function_name) __mock_##function_name(&minitestmocks, 
#define mocked(function_name) __mocked_##function_name(&minitestmocks)
#define release_mock(function_name) __release_##function_name(&minitestmocks);
#define mock_calls(function_name) __calls_##function_name(&minitestmocks)

extern MiniTestMockSuite minitestmocks;

#endif