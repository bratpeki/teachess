
# TeaChess - A chess explanation tool

## What is TeaChess?

TeaChess is a desktop program intended to be used for explaining chess games,
openings, puzzles and other forms of chess problems. Unlike other solutions,
TeaChess focuses on being fast, simple and extensible. Most functionality is
keyboard-based, allowing for quick and versitile usage.

## TCHS files

TeaChess has a specific file associated with it: the TCHS filetype (`.tchs`).
A standard TCHS file follows two rules:

1. It must be situated in the `./tchs/` directory
2. Its name must start with either `w`, which means "white", or `b`, which means black

Optionally, it should end with `.tchs`.

Its contents must contain 64 characters or less which can be:

1. `b/B`/bishop
2. `k/K`/king
3. `n/N`/knight
4. `p/P`/pawn
5. `q/Q`/queen
6. `r/R`/rook
7. `-/.`/blank

A normal TCHS file looks like this:

```sh
$ cat ./tchs/w-default.tchs
rnbqkbnr
pppppppp
--------
--------
--------
--------
PPPPPPPP
RNBKQBNR
```

## How is is made?

TeaChess is made using SDL2 for C.

