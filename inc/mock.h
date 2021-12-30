#ifndef __MINITEST_MOCKS_H__
#define __MINITEST_MOCKS_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MiniTestMockStruct {
  char* function;
  void* data;

  struct MiniTestMockStruct* next;
} MiniTestMock;

typedef struct MiniTestMockSuiteStruct {
  MiniTestMock *nodes;
} MiniTestMockSuite;

#define MT_FUNCTION_NO_RETURN_ERROR "Function %s has not been initialized with a return value."

#define mt_mock_forwards(function_name, return_type, ...)    \
  return_type __real_##function_name(__VA_ARGS__);           \
  return_type __wrap_##function_name(__VA_ARGS__);           \
  MiniTestMock* __init_##function_name(MiniTestMockSuite *s);\
                                                             \
  typedef struct __##function_name##Struct {                 \
    int loaded;                                              \
    return_type return_value;                                \
  } function_name##Struct;                                   \

#define mt_define_mock(function_name, return_type, ...)                 \
  MiniTestMock* __init_##function_name(MiniTestMockSuite *s) {          \
    MiniTestMock* node = malloc(sizeof(MiniTestMock));                  \
    node->next = NULL;                                                  \
                                                                        \
    function_name##Struct* data = malloc(sizeof(function_name##Struct)); \
    node->function = malloc(strlen(#function_name) + 1);                \
    strcpy(node->function, #function_name);                             \
    data->loaded = 0;                                                   \
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
    MiniTestMock* current_node = s->nodes;                                        \
    while(strcmp(current_node->function, #function_name)!=0) {                    \
      current_node = current_node->next;                                          \
    }                                                                             \
    if (strcmp(current_node->function, #function_name)!=0) {                      \
      current_node = __init_##function_name(s);                                   \
    }                                                                             \
    function_name##Struct* data = (function_name##Struct*)current_node->data;     \
    data->return_value = return_value;                                            \
    data->loaded = 1;                                                             \
  }                                                                               \

#define and_return(value) value);
#define mock(function_name) __mock_##function_name(&minitestmocks, 

extern MiniTestMockSuite minitestmocks;

#endif