#include "ruby.h"
#include "calc.cpp"

/* Backing Calculator */
Calculator *Calc = new Calculator();

/* Ruby method stubs */
extern "C" VALUE method_pushNumber(VALUE self, int num) {
    Calc->push(num);
    return (VALUE) 0;
}
extern "C" VALUE method_doOp(VALUE self, Op op, void (*printStackEntry)(int)) { 
    Calc-> /* | Stepping Point 1 | */
        doOp(op, printStackEntry); /* | Stepping Point 2 | */
    return 0; /* | Stepping Point 3 | */
}
extern "C" VALUE method_getResult(VALUE self) {
    int result = Calc->getResult();
    return INT2NUM(result);
}

/* setup Ruby module */
extern "C" void Init_CalcExt() {
    VALUE CalcExt = rb_define_module("CalcExt");

    /* initialize module methods */
    rb_define_method(CalcExt, "pushNumber", (VALUE (*)(...)) method_pushNumber, 1);
    rb_define_method(CalcExt, "doOp", (VALUE (*)(...)) method_doOp, 2);
    rb_define_method(CalcExt, "getResult", (VALUE (*)(...)) method_getResult, 0);

    /* initialize module fields */
    rb_define_const(CalcExt, "OP_ADD", INT2NUM(Op::ADD));
    rb_define_const(CalcExt, "OP_SUB", INT2NUM(Op::SUB));
    rb_define_const(CalcExt, "OP_MUL", INT2NUM(Op::MUL));
    rb_define_const(CalcExt, "OP_DIV", INT2NUM(Op::DIV));
    rb_define_const(CalcExt, "OP_PRINT", INT2NUM(Op::PRINT));
}
