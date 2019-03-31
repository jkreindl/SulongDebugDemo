require_relative "CalcExt"
include CalcExt

stack_entry_printer = -> (num){ puts '-> ' + num.to_s }
for operand in ARGV
    case operand
    when '+'
        CalcExt::doOp(CalcExt::OP_ADD, stack_entry_printer)
    when '-'
        CalcExt::doOp(CalcExt::OP_SUB, stack_entry_printer)
    when '*'
        CalcExt::doOp(CalcExt::OP_MUL, stack_entry_printer)
    when '/'
        CalcExt::doOp(CalcExt::OP_DIV, stack_entry_printer)
    when '='
        puts 'Stack Content (top-down):'
        CalcExt::doOp(CalcExt::OP_PRINT, stack_entry_printer)
    else
        num = Integer(operand)
        CalcExt::pushNumber(num)
    end
end
result = CalcExt::getResult()
puts 'The result is: ' + result.to_s
