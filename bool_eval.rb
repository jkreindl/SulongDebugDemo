require "./cext/BooleCext.su"
include BooleCext

args = ARGV.sort

$base_tokens = {
  '(' => -1, ')' => -2,
  '!' => -3, '&' => -4,
  '|' => -5, '->' => -6,
  '<-' => -7, '<->' => -8
}

def parse_tokens(tokens)
  num_vars = 0
  vars = Hash.new {|hash, sym|
    raise "Invalid name: " + sym unless /^[-_.\[\]$@\w]?[_.\[\]$@\w]$/.match? sym
    num_vars += 1
    hash[sym] = num_vars - 1
  }
  vars.merge!($base_tokens)

  peek = lambda do
    return tokens.empty? ? -1 : vars[tokens.first]
  end
  poll = lambda do
    return tokens.empty? ? -1 : vars[tokens.shift]
  end

  node = parse(peek, poll);
  [node, vars.invert, num_vars]
end

def find_solutions(node, num_vars)
  solutions = []
  (1 << num_vars).times do |n|
    res = eval(node, n);
    solutions << n if res == 1
  end
  solutions
end

def close_node(node)
  freeTree(node);
end

def print_solutions(file, solutions, vars, num_vars)
  format = (num_vars - 1).downto(0).to_a.map {|var_id| vars[var_id]}
  format = format.join(', ')
  format += " = %0" + num_vars.to_s + "b"
  puts 'Solutions for: ' + file
  solutions.each {|sol| puts format % [sol]}
  puts
  puts
end

def read_file(file)
  tokens = File.open(file, 'r').read
  tokens = tokens.split(/(&|!|\||<->?|->|\(|\))|\s+/)
  tokens = tokens.reject {|elt| elt.empty?}
  tokens
end

def handle_file(file)
  tokens = read_file file
  fn_node, vars, num_vars = parse_tokens tokens
  solutions = find_solutions(fn_node, num_vars)
  print_solutions(file, solutions, vars, num_vars)
  close_node fn_node
end

if args.empty?
  raise "Please supply at least one file as input!"
end

for file in args
  handle_file file
end
