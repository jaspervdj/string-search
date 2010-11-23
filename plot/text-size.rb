#!/usr/bin/ruby
require './plot/common.rb'

`./util/generate-text -s 20 -o tmp/pattern`

text_sizes = (2 .. 200)
create_csv text_sizes do |text_size|
    `./util/generate-text -s #{text_size * 1024} -o tmp/text`

    with_algorithms do |algorithm|
        bench algorithm, "tmp/pattern", "tmp/text"
    end
end
