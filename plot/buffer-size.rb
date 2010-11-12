#!/usr/bin/ruby
require 'fileutils'
require './plot/common.rb'

def change_buffer_size buffer_size
    with_file "src/common.c" do |text|
        text.gsub! /^#define DEFAULT_BUFFER_SIZE .*$/,
                "#define DEFAULT_BUFFER_SIZE #{buffer_size}"
    end
end

def main
    buffer_size = 16
    results_file = "results.csv"

    # Clear file
    FileUtils.rm_f results_file

    20.times do
        change_buffer_size buffer_size

        `make`
        mean = bench "bin/bench0", "data/zoekterm", "data/kjv"
        File.open results_file, "a" do |file|
            file.write "#{buffer_size},#{mean}\n"
        end

        buffer_size = buffer_size * 2
    end
end

main
