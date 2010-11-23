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
create_csv range_sizes do |range_size|
    File.open "tmp/characters", "w" do |file|
        file.write(character_range range_size)
    end

    `./util/generate-text -f tmp/characters -s 1000 -o tmp/pattern`
    `./util/generate-text -f tmp/characters -s 300000 -o tmp/text`

    with_algorithms do |algorithm|
        bench algorithm, "tmp/pattern", "tmp/text"
    end
end
