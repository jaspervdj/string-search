#!/usr/bin/ruby
require './plot/common.rb'

def change_buffer_size buffer_size
    text = File.read "src/common.c"
    text.gsub! /^#define DEFAULT_BUFFER_SIZE .*$/,
            "#define DEFAULT_BUFFER_SIZE #{buffer_size}"
    File.open "src/common.c", "w" do |file|
        file.write text
    end
end

def main
    buffer_size = 16
    results_file = "results.csv"

    # Clear file
    File.open results_file, "w" do end

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
