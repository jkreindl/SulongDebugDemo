#include "calc.cpp"

static Calculator *Calc = new Calculator;

extern "C" const Op getOpAdd() {
    return Op::ADD;
}

extern "C" const Op getOpSub() {
    return Op::SUB;
}

extern "C" const Op getOpMul() {
    return Op::MUL;
}

extern "C" const Op getOpDiv() {
    return Op::DIV;
}

extern "C" const Op getOpPrint() {
    return Op::PRINT;
}

extern "C" void doOp(Op op, void(*printStack)(int)) {
    Calc->doOp(op, printStack);
}

extern "C" void pushNumber(int num) {
    Calc->push(num);
}

extern "C" int getResult() {
    return Calc->getResult();
}