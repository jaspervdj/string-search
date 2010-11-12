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
