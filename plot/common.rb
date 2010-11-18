require 'tempfile'

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

def with_file file_name
    content = File.read file_name
    File.open file_name, "w" do |file|
        file.write(yield content)
    end
end

def benchmark points
    results_file = "results.csv"
    FileUtils.rm_f results_file
    points.each do |point|
        # Run the benchmark once
        puts "Running benchmark for point #{point}..."
        results = yield point

        # Write as CSV
        fields = [point] + results
        File.open results_file, "a" do |file|
            file.write "#{fields.join ','}\n"
        end
    end
end

def with_algorithms
    algorithms = ["bin/bench0", "bin/bench1", "bin/bench2"]
    algorithms.map do |algorithm| yield algorithm end
end
