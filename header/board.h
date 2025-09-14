#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>

// Function declarations
void createBoard(char ***board, int n);
void printBoard(char **board, int n);
void clearBoard(char ***board, int n);
void freeBoard(char ***board, int n);

#endif
