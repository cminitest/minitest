#include "minitest.h"

MiniTestMock* mt_find_node(MiniTestMockSuite *s, char* function_name) {
  MiniTestMock* current_node = s->nodes;    
                                    
  while(strcmp(current_node->function, function_name) != 0) {                    
    current_node = current_node->next;                                          
  }
                                                                
  if (strcmp(current_node->function, function_name) != 0 ) {                      
    current_node = NULL;                                   
  }

  return current_node;                                        
}

MiniTestMockSuite minitestmocks = {
  .nodes = NULL
};