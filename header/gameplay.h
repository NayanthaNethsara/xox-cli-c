#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <stdio.h>
#include "board.h"
#include "filewrite.h"

// Function declarations
int checkDraw(int moves, int n, const char *filename);
int checkWin(char **board, int n, char player, int lastMove[2], const char *filename);
void move(char ***board, int n, int *moves, char player, int *coordinate);
void playGame(char ***board, int n, int *moves, int *coordinate, char currentPlayer, const char *filename);

#endif
