require "./cext/BooleCext.su"
include BooleCext

# for tokenizing operators
$base_tokens = {
  '(' => BooleCext::TOKEN_LPAR, ')' => BooleCext::TOKEN_RPAR, '!' => BooleCext::TOKEN_NOT,
   '<->' => BooleCext::TOKEN_EQUALS, '&' => BooleCext::TOKEN_AND, '|' => BooleCext::TOKEN_OR,
  '->' => BooleCext::TOKEN_IMPL, '<-' => BooleCext::TOKEN_IMPL_REVERSE
}

# read the file content and split it into string tokens
def read_file(file)
  tokens = File.open(file, 'r').read
  tokens = tokens.split(/(&|!|\||<->?|->|\(|\))|\s+/) .reject {|elt| elt.empty?}
  tokens
end

# parse string tokens into a formula AST
def parse_tokens(tokens)
  # convert string tokens to integer tokens for the C parsing code
  num_vars = 0
  vars = Hash.new {|hash, sym|
    raise "Invalid name: " + sym unless /^[-_.\[\]$@\w]?[_.\[\]$@\w]$/.match? sym
    num_vars += 1
    hash[sym] = num_vars - 1
  }
  vars.merge!($base_tokens)

  # emulate a lexer for the C parsing code
  peek = -> (){ tokens.empty? ? -1 : vars[tokens.first] }
  poll = -> (){ tokens.empty? ? -1 : vars[tokens.shift] }

  # parse the tokens into a formula AST in C
  ast_root = parse(peek, poll);
  [ast_root, vars.invert, num_vars]
end

# check all possible assignments whether or not they satisfy the formula AST
def find_solutions(ast_root, num_vars)
  solutions = []
  (1 << num_vars).times do |n|
    res = eval(ast_root, n);
    solutions << n if res == 1
  end
  solutions
end

# print all assignments that satisfy the formula AST
def print_solutions(file, solutions, vars, num_vars)
  format = (num_vars - 1).downto(0).to_a.map {|var_id| vars[var_id]}
  format = format.join(', ') +  " = %0" + num_vars.to_s + "b"
  puts 'Solutions for: ' + file
  solutions.each {|sol| puts format % [sol]}
end

# deallocate the formula AST
def close_node(ast_root)
  freeTree(ast_root);
end

# parse and evaluate a given *.boole file
def handle_file(file)
  tokens = read_file file
  fn_node, vars, num_vars = parse_tokens tokens
  solutions = find_solutions(fn_node, num_vars)
  print_solutions(file, solutions, vars, num_vars)
  close_node fn_node
end

# parse and evaluate all specified *.boole files
raise "Please supply at least one file as input!" if ARGV.empty?
for file in ARGV.sort
  handle_file file
end
