#!/usr/bin/ruby
require 'fileutils'
require './plot/common.rb'

def change_buffer_size buffer_size
    with_file "src/common.c" do |text|
        text.gsub! /^#define DEFAULT_BUFFER_SIZE .*$/,
                "#define DEFAULT_BUFFER_SIZE #{buffer_size}"
    end
end

buffer_sizes = (4 .. 10).map do |n| 2 ** n end
benchmark buffer_sizes do |buffer_size|
    change_buffer_size buffer_size
    `make`
    mean = bench "bin/bench0", "data/zoekterm", "data/kjv"
    [mean]
end
