require 'tempfile'

# Run a benchmark
#
def bench benchmark, pattern, text
    # Create a tempfile
    tmp = Tempfile.new "bench"
    tmp.close

    # Run the benchmark, save results to tempfile
    `#{benchmark} -n 10 -w 3 -o #{tmp.path} #{pattern} #{text} >/dev/null`

    # Read tempfile, find mean and return it
    out = File.read(tmp.path)
    tmp.delete
    mean = (out.lines.grep /^Mean: /).first.gsub /^Mean: /, ""
    mean.to_f
end

# Modify a file in-place
#
def with_file file_name
    content = File.read file_name
    File.open file_name, "w" do |file|
        file.write(yield content)
    end
end

# Execute a benchmark for every data point, writing the results to results.csv
#
def create_csv points
    File.open "results.csv", "w" do |file|
        points.each do |point|
            # Run the benchmark once
            puts "Running benchmark for data point #{point}..."
            results = yield point

            # Write as CSV
            fields = [point] + results
            file.write "#{fields.join ','}\n"
        end
    end
end

# Execute a block with all algorithms
#
def with_algorithms
    algorithms = ["bin/bench0", "bin/bench1", "bin/bench2", "bin/bench3"]
    algorithms.map do |algorithm| yield algorithm end
end
