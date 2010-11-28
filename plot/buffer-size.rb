#!/usr/bin/ruby
require 'fileutils'
require './plot/common.rb'

def change_buffer_size buffer_size
    with_file "src/common.c" do |text|
        text.gsub! /^#define DEFAULT_BUFFER_SIZE .*$/,
                "#define DEFAULT_BUFFER_SIZE #{buffer_size}"
    end
end

buffer_sizes = (4 .. 16).map do |n| 2 ** n end
create_csv buffer_sizes do |buffer_size|
    change_buffer_size buffer_size
    `make`
    with_algorithms do |name, algorithm|
        bench algorithm, "data/zoekterm", "data/kjv"
    end
end
