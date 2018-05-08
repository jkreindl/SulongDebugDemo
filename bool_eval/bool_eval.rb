# import the C functions
Polyglot::eval_file("llvm", "c_boole.bc");

args = ARGV.sort

# ids to represent operators are negative to separate them from variables
$base_tokens = {
  '(' => -1, ')' => -2,
  '!' => -3, '&' => -4,
  '|' => -5, '->' => -6,
  '<-' => -7, '<->' => -8
}

# parse *.boole file content into an AST
def parse_tokens(tokens)
  num_vars = 0
  vars = Hash.new {|hash, sym|
    # each named variable receives a unique, positive integer id
    raise "Invalid name: " + sym unless /^[-_.\[\]$@\w]?[_.\[\]$@\w]$/.match? sym
    num_vars += 1
    hash[sym] = num_vars - 1
  }
  vars.merge!($base_tokens)

  # these act as a lexer for the C parser
  peek = lambda do
    return tokens.empty? ? -1 : vars[tokens.first]
  end
  poll = lambda do
    return tokens.empty? ? -1 : vars[tokens.shift]
  end

  # parse the tokens into a boole AST
  parse = Truffle::Interop.import('@parse')
  node = Truffle::Interop.execute(parse, peek, poll)
  [node, vars.invert, num_vars]
end

# find all satisfying assignments for the given boole AST
def find_solutions(node, num_vars)
  eval = Truffle::Interop.import('@eval')
  solutions = []
  (1 << num_vars).times do |n|
    # the bit at index y in the input represents the variable with id y
    res = Truffle::Interop.execute(eval, node, n)
    solutions << n if res == 1
  end
  solutions
end

# deallocate the boole AST
def close_node(node)
  free_node = Truffle::Interop.import('@freeTree')
  Truffle::Interop.execute(free_node, node)
end

# print all satisfying assignments to the console
def print_solutions(file, solutions, vars, num_vars)
  format = (num_vars - 1).downto(0).to_a.map {|var_id| vars[var_id]}
  format = format.join(', ')
  format += " = %0" + num_vars.to_s + "b"
  puts 'Solutions for: ' + file
  solutions.each {|sol| puts format % [sol]}
  puts
end

# tokenize the content of a *.boole file
def read_file(file)
  tokens = File.open(file, 'r').read
  tokens = tokens.split(/(&|!|\||<->?|->|\(|\))|\s+/)
  tokens = tokens.reject {|elt| elt.empty?}
  tokens
end

# parse a boole formula from the file and print all assignments that satisfy it
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
