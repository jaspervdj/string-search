#!/bin/bash

PATTERN=data/zoekterm
TEXT=/tmp/text
MATCHES=/tmp/matches
EXPECTED_MATCHES=/tmp/expected-matches

function make-pipe {
    rm -f "$1"
    mkfifo "$1"
}

make-pipe "$TEXT"
make-pipe "$MATCHES"
make-pipe "$EXPECTED_MATCHES"

# Search the text for matches
./search1 "$PATTERN" "$TEXT" >"$MATCHES" &

# Generate the text and expected matches
./util/generate-text-and-matches "$PATTERN" "$TEXT" "$EXPECTED_MATCHES" &

# Compare the matches and expected matches
# diff --speed-large-files "$MATCHES" "$EXPECTED_MATCHES"
