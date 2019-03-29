require_relative("FactExt")
include FactExt

(0..12).each do |n|
    f = FactExt::fact(n)
    puts "fact(" + n.to_s + ") = " + f.to_s
end
