#!/usr/bin/ruby
require 'fileutils'
require './plot/common.rb'

# Generate a string containing n different characters
#
def character_range n
    chars = (0 .. n).to_a.map do |x| x.chr end
    chars.join
end

range_sizes = (2 .. 200)
benchmark range_sizes do |range_size|
    File.open "tmp/characters", "w" do |file|
        file.write(character_range range_size)
    end

    `./util/generate-text -f tmp/characters -s 1 -o tmp/query`
    `./util/generate-text -f tmp/characters -s 300 -o tmp/text`

    mean = bench "bin/bench2", "tmp/query", "tmp/text"
    [mean]
end
