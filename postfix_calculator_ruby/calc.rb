require_relative "CalcExt"
include CalcExt

for operand in ARGV
    case operand
    when '+'
        CalcExt::doOp(CalcExt::OP_ADD)
    when '-'
        CalcExt::doOp(CalcExt::OP_SUB)
    when '*'
        CalcExt::doOp(CalcExt::OP_MUL)
    when '/'
        CalcExt::doOp(CalcExt::OP_DIV)
    when '='
        stack = CalcExt::doOp(CalcExt::OP_PRINT)
        puts 'Stack Content (top-down):'
        stack.each { |elt| puts elt.to_s }
    else
        num = Integer(operand)
        CalcExt::pushNumber(num)
    end
end
done = nil
result = CalcExt::getResult
puts 'The result is: ' + result.to_s
