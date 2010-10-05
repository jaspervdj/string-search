#!/bin/awk -f
# Usage: awk -f search.awk -v pattern=Jesus kjv

BEGIN {
    count = 0
}

{
    result = index($0, pattern)
    while(result >= 1) {
        count += 1
        $0 = substr($0, result + length(pattern))
        result = index($0, pattern)
    }
}

END {
    printf("Matches found: %d", count)
}
