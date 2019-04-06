#include <ruby.h>
#include <calc.h>

static Calculator * calc;

/* Ruby method proxy */
VALUE method_pushNumber(VALUE self, VALUE numberValue) {
    int number = NUM2INT(numberValue);
    push(calc, number);
    return INT2NUM(0);
}

/* Ruby method proxy */
VALUE method_getResult(VALUE self) {
    int result = getResult(calc);
    return INT2NUM(result);
}

/* Ruby method proxy */
VALUE method_doOp(VALUE self, VALUE opValue) {
    Op op = NUM2INT(opValue);
    doOp(calc, op);
    return INT2NUM(0);
}

VALUE method_getStack(VALUE self) {
    VALUE ary = rb_ary_new();
    long ary_offset = 0L;
    for (struct StackEntry *entry = calc->top; entry ; entry = entry->next) {
        const int value = entry->num;
        rb_ary_store(ary, ary_offset++, INT2NUM(value));
    }
    return ary;
}

void Init_CalcExt() {
    /* Initialize Ruby module and C calculator */
    calc = calloc(1, sizeof(Calculator));
    VALUE CalcExt = rb_define_module("CalcExt");

    /* initialize module methods */
    rb_define_method(CalcExt, "pushNumber", method_pushNumber, 1);
    rb_define_method(CalcExt, "doOp", method_doOp, 1);
    rb_define_method(CalcExt, "getStack", method_getStack, 0);
    rb_define_method(CalcExt, "getResult", method_getResult, 0);

    /* initialize module fields */
    rb_define_const(CalcExt, "OP_ADD", INT2NUM(ADD));
    rb_define_const(CalcExt, "OP_SUB", INT2NUM(SUB));
    rb_define_const(CalcExt, "OP_MUL", INT2NUM(MUL));
    rb_define_const(CalcExt, "OP_DIV", INT2NUM(DIV));
}