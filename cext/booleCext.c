#include "ruby.h"
#include "boole.h"

VALUE BooleCext = NULL;

void Init_BooleCext();

VALUE method_parse(VALUE self, VALUE peek, VALUE pop);
VALUE method_eval(VALUE self,  VALUE root, VALUE vars);
VALUE method_freeTree(VALUE self, VALUE root);

void Init_BooleCext() {
    BooleCext = rb_define_module("BooleCext");

    /* initialize module methods */
    rb_define_method(BooleCext, "parse", method_parse, 2);
    rb_define_method(BooleCext, "eval", method_eval, 2);
    rb_define_method(BooleCext, "freeTree", method_freeTree, 1);

    /* initialize module fields */
    rb_define_const(BooleCext, "TOKEN_LPAR", INT2NUM(TOKEN_LPAR));
    rb_define_const(BooleCext, "TOKEN_RPAR", INT2NUM(TOKEN_RPAR));
    rb_define_const(BooleCext, "TOKEN_NOT", INT2NUM(TOKEN_NOT));
    rb_define_const(BooleCext, "TOKEN_EQUALS", INT2NUM(TOKEN_EQUALS));
    rb_define_const(BooleCext, "TOKEN_AND", INT2NUM(TOKEN_AND));
    rb_define_const(BooleCext, "TOKEN_OR", INT2NUM(TOKEN_OR));
    rb_define_const(BooleCext, "TOKEN_IMPL", INT2NUM(TOKEN_IMPL));
    rb_define_const(BooleCext, "TOKEN_IMPL_REVERSE", INT2NUM(TOKEN_IMPL_REVERSE));
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
