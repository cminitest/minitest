int add_ints(int n1, int n2) {
  return n1 + n2;
}

int add_three_ints(int n1, int n2, int n3) {
  return add_ints(add_ints(n1,n2), n3);
}