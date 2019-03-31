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

/* used to return the stack content to Ruby */
VALUE ary;
long ary_offset;
void addToAry(int value) {{
    if (ary == 0L) { ary = rb_ary_new(); ary_offset = 0L; }
    rb_ary_store(ary, ary_offset++, INT2NUM(value));
}}

/* Ruby method proxy */
VALUE method_doOp(VALUE self, VALUE opValue) {
    Op op = NUM2INT(opValue);
    doOp(calc, op, &addToAry);
    if (op == PRINT) {
        // don't keep the global ary around after returning
        VALUE result = ary;
        ary = ary_offset = 0L;
        return result;

    } else {
        return INT2NUM(0);
    }
}

void Init_CalcExt() {
    /* Initialize Ruby module and C calculator */
    calc = calloc(1, sizeof(Calculator));
    ary = 0L; ary_offset = 0L;
    VALUE CalcExt = rb_define_module("CalcExt");

    /* initialize module methods */
    rb_define_method(CalcExt, "pushNumber", method_pushNumber, 1);
    rb_define_method(CalcExt, "doOp", method_doOp, 1);
    rb_define_method(CalcExt, "getResult", method_getResult, 0);

    /* initialize module fields */
    rb_define_const(CalcExt, "OP_ADD", INT2NUM(ADD));
    rb_define_const(CalcExt, "OP_SUB", INT2NUM(SUB));
    rb_define_const(CalcExt, "OP_MUL", INT2NUM(MUL));
    rb_define_const(CalcExt, "OP_DIV", INT2NUM(DIV));
    rb_define_const(CalcExt, "OP_PRINT", INT2NUM(PRINT));
}