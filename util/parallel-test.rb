#!/usr/bin/ruby
require 'fileutils'

algorithms = ["bin/search0", "bin/search1", "bin/search2", "bin/search3"]

# Create a named pipe
#
def make_pipe name
    FileUtils.rm_f name
    `mkfifo #{name}`
end

# Start a text generator
#
pattern = "tmp/pattern"
text = "tmp/text"
matches = "tmp/matches"
make_pipe text
make_pipe matches
`util/generate-text -s 5 -c '\nfooo' -o #{pattern}`
fork do
    `util/generate-text-and-matches #{pattern} #{text} #{matches}`
end
input_pipes = []
output_pipes = [matches]

# Start algorithms on every pipe
#
pipe_id = 0
algorithms.each do |algorithm|
    input_pipe = "tmp/pipe-#{pipe_id}-in"
    output_pipe = "tmp/pipe-#{pipe_id}-out"
    make_pipe input_pipe
    make_pipe output_pipe
    puts "Starting #{algorithm}..."
    fork do
        `#{algorithm} #{pattern} #{input_pipe} | sed 's/.*://' >#{output_pipe}`
    end
    input_pipes << input_pipe
    output_pipes << output_pipe
    pipe_id = pipe_id + 1
end

# Read the input and spread it over the pipes
#
fork do
    `cat #{text} | tee #{input_pipes.join ' '}`
end

# Start the pipe-diff utility
#
sleep 1
exec "util/pipe-diff #{output_pipes.join ' '}"
