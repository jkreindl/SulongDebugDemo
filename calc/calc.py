from sys import argv

import polyglot
polyglot.eval(path="calc-pyext.bc", language="llvm")

def getOpId(name):
    func = polyglot.import_value("@getOp" + name)
    op = func()
    return op

op_add = getOpId("Add")
op_sub = getOpId("Sub")
op_mul = getOpId("Mul")
op_div = getOpId("Div")
op_print = getOpId("Print")

c_op = polyglot.import_value("@doOp")
c_push = polyglot.import_value("@pushNumber")
c_result = polyglot.import_value("@getResult")

def stack_entry_printer(num):
    print('->', str(num))

for operand in argv[1:]:
    if '+' == operand:
        c_op(op_add, stack_entry_printer)
    elif '-' == operand:
        c_op(op_sub, stack_entry_printer)
    elif '*' == operand:
        c_op(op_mul, stack_entry_printer)
    elif '/' == operand:
        c_op(op_div, stack_entry_printer)
    elif '=' == operand:
        print('Stack Content (top-down):')
        c_op(op_print, stack_entry_printer)
    else:
        num = int(operand)
        c_push(num)

result = c_result()
print('The result is:', str(result))
