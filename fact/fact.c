#include "ruby.h"

int fact(int n) {
  int result = 1;
  if (n > 0)
    result = n * fact(n - 1);
  return result;
}

int callFact(VALUE self, int n) {
    return fact(n);
}

void Init_FactExt() {
    VALUE FactExt = rb_define_module("FactExt");
    rb_define_method(FactExt, "fact", &callFact, 1);
}
