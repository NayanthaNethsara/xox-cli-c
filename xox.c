#include <stdio.h>
#include <stdlib.h>
#include "header/board.h"
#include "header/filewrite.h"
#include "header/gameplay.h"

int main()
{
    int n, moves = 0;
    char **board;
    int *coordinate = (int *)malloc(2 * sizeof(int));
    const char *filename = "output.txt";

    // Get a valid board size (n should be >= 3)
    getBoardSize(&n);

    // Write the board size to the output file
    char msg[50];
    sprintf(msg, "Board Size is: %d", n);
    writeFile(msg, filename);

    // Create and initialize the tic tac board
    createBoard(&board, n);
    clearBoard(&board, n);
    printBoard(board, n);
    writeMoves(board, n, filename);

    //  Game loop
    playGame(&board, n, &moves, coordinate, 'X', filename);

    // Free memory used by the board
    freeBoard(&board, n);

    return 0;
}
