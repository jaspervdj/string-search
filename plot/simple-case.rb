#!/usr/bin/ruby
require './plot/common.rb'

if ARGV.length < 2 then
    puts "Usage: #{$0} <pattern> <file>"
    exit 1
end

results = with_algorithms do |name, algorithm|
    time = bench algorithm, ARGV[0], ARGV[1]
    {name => time}
end

results = results.reduce :merge
table = results.map do |name, time|
    "    #{name} & #{time} \\\\" 
end
table = table.join "\n"

puts <<HERE
\\begin{center}
\\begin{tabular}{lr}
    Algoritme & Uitvoeringstijd (in s) \\\\
#{table}
\\end{tabular}
\\end{center}
HERE
