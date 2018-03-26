#include "ruby.h"
#include "boole.h"

VALUE BooleCext = NULL;

void Init_BooleCext();

VALUE method_parse(VALUE self, VALUE peek, VALUE pop);
VALUE method_eval(VALUE self,  VALUE root, VALUE vars);
VALUE method_freeTree(VALUE self, VALUE root);

void Init_BooleCext() {
    BooleCext = rb_define_module("BooleCext");
    rb_define_method(BooleCext, "parse", method_parse, 2);
    rb_define_method(BooleCext, "eval", method_eval, 2);
    rb_define_method(BooleCext, "freeTree", method_freeTree, 1);
}

VALUE method_parse(VALUE self, VALUE peek, VALUE pop) {
    return parse(peek, pop);
}

VALUE method_eval(VALUE self, VALUE root, VALUE vars) {
    return INT2NUM(eval(root, vars));
}

VALUE method_freeTree(VALUE self, VALUE root) {
    freeTree(root);
    return 0;
}
