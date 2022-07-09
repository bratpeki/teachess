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

1.  `-/.`/blank
2.  `b/B`/bishop
3.  `c/C`/king which castle on either side
4.  `e/E`/pawn which can be eaten via "En passant"
5.  `j/J`/king which castle on the left side
6.  `k/K`/king
7.  `l/L`/king which castle on the right side
8.  `n/N`/knight
9.  `p/P`/pawn
10. `q/Q`/queen
11. `r/R`/rook

A normal TCHS file looks like this:

```sh
$ cat ./tchs/wDefault.tchs
rnbqcbnr
pppppppp
--------
--------
--------
--------
PPPPPPPP
RNBQCBNR
```

## How is it made?

TeaChess is made using SDL2 for C.
