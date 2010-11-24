#!/usr/bin/ruby

# Test by generating a file containing predicatable, overlapping matches

if ARGV.length < 1 then
    puts "Usage: #{$0} <algorithm> [<algorithm> ...]"
    exit 1
end

# Create an overlapping pattern
matches_every = 10
pattern = `util/generate-text -c abcdef -s #{matches_every}`
pattern = pattern + pattern
File.open "tmp/pattern", "w" do |file| file.write pattern end

# Generate the text
text_size = rand(200)
File.open "tmp/text", "w" do |file|
    text_size.times do file.write pattern end
end

# Generate the expected matches
File.open "tmp/expected-matches", "w" do |file|
    (text_size * 2 - 1).times do |i|
        file.write "tmp/text:#{1 + i * matches_every}\n"
    end
end

ARGV.each do |algorithm|
    # Run and check
    `#{algorithm} tmp/pattern tmp/text > tmp/matches`
    unless `diff tmp/matches tmp/expected-matches`.empty?
        puts "Test failed!"
    end
end
