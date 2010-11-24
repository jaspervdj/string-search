#!/usr/bin/ruby

# Test by comparing the results of two algorithms

NUMBER_OF_TESTS = 100
CHARACTERS = ('a' .. 'd').to_a.join

if ARGV.length < 2 then
    puts "Usage: #{$0} <algorithm1> <algorithm2>"
    exit 1
end

NUMBER_OF_TESTS.times do
    `util/generate-text -c #{CHARACTERS} -s 7 -r #{rand(10000)} -o tmp/pattern`
    `util/generate-text -c #{CHARACTERS} -s 20000 -r #{rand(10000)} -o tmp/text`
    `#{ARGV[0]} tmp/pattern tmp/text > tmp/matches-1`
    `#{ARGV[1]} tmp/pattern tmp/text > tmp/matches-2`
    unless `diff tmp/matches-1 tmp/matches-2`.empty?
        puts "Test failed!"
    end
end
