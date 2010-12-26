string-search
What
----

This project is an implementation of several fast exact string searching
algorithms. It provides 6 executables:

- `bin/search0`: Brute-force
- `bin/search1`: Shift-and
- `bin/search1-bit-vector`: Bit-vector version of the Shift-and algorithm
- `bin/search2`: Knuth-Morris-Pratt
- `bin/search3`: Boyer-Moore-Horspool
- `bin/search4`: Rabin-Karp

Compiling
---------

    mkdir bin
    cmake .
    make

Running
-------

    ./bin/searchX pattern-file [files ...]

Status
------

There is a known issue in `search1`: when searching for the pattern `aaaa` in
the text `aaaaaaaaa`, the algorithm will find one *before* the start of the
file. This is probably caused by the optimizations there. I don't know if I will
ever fix this bug, since the project has been handed in now.
