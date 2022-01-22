#include <stdlib.h>

int add_ints(int n1, int n2) {
  return n1 + n2;
}

int add_three_ints(int n1, int n2, int n3) {
  return add_ints(add_ints(n1,n2), n3);
}

void person_constructor(char* name, short age) {}

void test_char(char n){ }
void test_short(short n){ }
void test_long(long n){ }
void test_double(double n){ }
void test_float(float n){ }
void test_void_ptr(void* n){ }
void test_char_ptr(char* n){ }
void test_size_t(size_t n){ }
void test_u_int(unsigned int n){ }
void test_u_short(unsigned short n){ }
void test_u_char(unsigned char n){ }
void test_int_array(int* n){ }
void test_short_array(short* n){ }
void test_long_array(long* n){ }
void test_double_array(double* n){ }
void test_float_array(float* n){ }