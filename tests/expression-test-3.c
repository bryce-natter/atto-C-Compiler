/* expression-test-3.c

   A bunch of functions testing various arithmetic expressions.
   These functions are to be called from a driver program to
   check for correctness.

*/

int add_test(int a, int b)
{ return a + b;
}

int sub_test(int a, int b)
{ return a - b;
}

int mul_test(int a, int b)
{ return a * b;
}

int div_test(int a, int b)
{ return a / b;
}

int eq_test(int a, int b)
{ return a == b;
}

int neq_test(int a, int b)
{ return a != b;
}

int gt_test(int a, int b)
{ return a > b;
}

int ge_test(int a, int b)
{ return a >= b;
}

int lt_test(int a, int b)
{ return a < b;
}

int le_test(int a, int b)
{ return a < b;
}

int neg_test(int a)
{ return -a;
}

int and_test(int a, int b)
{ return a && b;
}

int or_test(int a, int b)
{ return a || b;
}

int not_test(int a)
{ return !a;
}



