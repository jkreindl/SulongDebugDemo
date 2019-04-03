require_relative "CalcExt"
include CalcExt

def parse_number(operand)
    num = Integer(operand)
    CalcExt::pushNumber(num)
end

def print_stack()
    stack = CalcExt::doOp(CalcExt::OP_PRINT)
    puts 'Stack Content (top-down):'
    stack.each { |elt| puts elt.to_s }
end

args = ARGV
args.each { |operand|
    case operand
    when '+' then CalcExt::doOp(CalcExt::OP_ADD)
    when '-' then CalcExt::doOp(CalcExt::OP_SUB)
    when '*' then CalcExt::doOp(CalcExt::OP_MUL)
    when '/' then CalcExt::doOp(CalcExt::OP_DIV)
    when '=' then print_stack()
    else          parse_number(operand)
    end
}

result = CalcExt::getResult
puts 'The result is: ' + result.to_s
