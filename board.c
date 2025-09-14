#include "header/board.h"

// Function to create the game board using dynamic allocation
void createBoard(char ***board, int n)
{
    *board = (char **)malloc(n * sizeof(char *));

    for (int i = 0; i < n; i++)
    {
        (*board)[i] = (char *)malloc(n * sizeof(char));
    }
}

// Function to print the game board
void printBoard(char **board, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c", board[i][j]);
            if (j != n - 1)
            {
                printf(" | ");
            }
        }
        printf("\n");
    }
}

// Function to clear the game board
void clearBoard(char ***board, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            (*board)[i][j] = ' ';
        }
    }
}

// Function to free memory used by the board
void freeBoard(char ***board, int n)
{
    for (int i = 0; i < n; i++)
    {
        // Free Row
        free((*board)[i]);
    }
    free(*board);
}
