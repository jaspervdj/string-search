string-search
=============

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

    cmake .
    make

Running
-------

    ./bin/searchX pattern-file [files ...]
