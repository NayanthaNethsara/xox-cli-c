# Tic-Tac-Toe Game in C

## Overview

A dynamic n x n Tic-Tac-Toe game implemented in C.  
Supports user input, win/draw detection, and logging moves to a file.

---

## Build & Run

### Compile

To compile the single-file version:

```bash
gcc xox-single.c -o xox.o
```

### Or with Make

a header-based modular build. All logic is separated into `.h` and `.c` files for better organization and maintainability.

```bash
make
```

### Run

```bash
./xox.o
```

## Game Play

- Players take turns (X and O) entering coordinates in the format `row,column`.
- The board size is user-defined (minimum 3x3).
- Moves and results are logged to `output.txt`.

## Scope

- Supports variable board sizes (n ≥ 3).
- Dynamic memory allocation for the board.
- Tracks moves and detects wins/draws.
- Saves moves and messages to an output file.

## Known Issues

- Input is not fully sanitized: entering invalid characters can crash the program.
- Buffer is not cleared on invalid input.
- Only numeric input is expected; non-numeric input may cause segmentation faults.
- Recursive `playGame` could cause stack overflow on extremely large boards.
