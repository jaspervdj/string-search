#!/usr/bin/ruby
require './plot/common.rb'

`./tests/generate-text -s 20 -o tmp/pattern`

text_sizes = (2 .. 200)
create_csv text_sizes do |text_size|
    `./tests/generate-text -s #{text_size * 1024} -o tmp/text`

    with_algorithms do |name, algorithm|
        bench algorithm, "tmp/pattern", "tmp/text"
    end
end
