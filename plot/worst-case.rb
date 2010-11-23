#!/usr/bin/ruby
require 'fileutils'
require './plot/common.rb'

# Generate a file with the contents "aaa...b". File size is expressed in 1024
# byte chunks.
#
def worst_case file_name, file_size
    File.open file_name, "w" do |file|
        as = "a" * (file_size * 1024 - 1)
        file.write(as + "b")
    end
end

text_file_size = 20
worst_case "tmp/text", text_file_size

pattern_file_sizes = (1 .. text_file_size)
create_csv pattern_file_sizes do |pattern_file_size|
    worst_case "tmp/pattern", pattern_file_size

    with_algorithms do |algorithm|
        bench algorithm, "tmp/pattern", "tmp/text"
    end
end
