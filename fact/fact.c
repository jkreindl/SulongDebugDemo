#include "ruby.h"

int fact(int n) {
  int result = 1;
  if (n > 0)
    result = n * fact(n - 1);
  return result;
}

VALUE callFact(VALUE self, VALUE num) {
  int n = NUM2INT(num);
  int result = fact(n);
  return INT2NUM(result);
}

void Init_FactExt() {
  VALUE FactExt = rb_define_module("FactExt");
  rb_define_method(FactExt, "fact", &callFact, 1);
}
