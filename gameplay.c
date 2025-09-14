#include "header/gameplay.h"

// Helper functions to check rows, columns, and diagonals for a win
static int checkMainDiagonal(char **board, int n, char player)
{
    for (int i = 0; i < n; i++)
    {
        if (board[i][i] != player) return 0;
    }
    return 1;
}

static int checkAntiDiagonal(char **board, int n, char player)
{
    for (int i = 0; i < n; i++)
    {
        if (board[i][n - 1 - i] != player) return 0;
    }
    return 1;
}

static int checkColumn(char **board, int n, char player, int col)
{
    for (int i = 0; i < n; i++)
    {
        if (board[i][col] != player) return 0;
    }
    return 1;
}

static int checkRow(char **board, int n, char player, int row)
{
    for (int i = 0; i < n; i++)
    {
        if (board[row][i] != player) return 0;
    }
    return 1;
}

static int win(char player, const char *filename)
{
    char msg[50];
    sprintf(msg, "Congratulations! %c wins the game.\n", player);
    printf("%s", msg);
    writeFile(msg, filename);
    return 1;
}

// Function to check for a draw
int checkDraw(int moves, int n, const char *filename)
{
    if (moves >= n * n)
    {
        const char *msg = "Draw! No possible moves.\n";
        printf("%s", msg);
        writeFile(msg, filename);
        return 1;
    }
    return 0;
}

// Function to check for a win
int checkWin(char **board, int n, char player, int lastMove[2], const char *filename)
{
    if (lastMove[0] == lastMove[1] && checkMainDiagonal(board, n, player)) return win(player, filename);
    if (lastMove[0] == n - 1 - lastMove[1] && checkAntiDiagonal(board, n, player)) return win(player, filename);
    if (checkColumn(board, n, player, lastMove[1])) return win(player, filename);
    if (checkRow(board, n, player, lastMove[0])) return win(player, filename);

    return 0;
}

// Function for a player to make a move
void move(char ***board, int n, int *moves, char player, int *coordinate)
{
    char c;
    do
    {
        printf("Move (%c): ", player);
        scanf("%d%c%d", &coordinate[0], &c, &coordinate[1]);
    } while (coordinate[0] >= n || coordinate[1] >= n || coordinate[0] < 0 || coordinate[1] < 0 || (*board)[coordinate[0]][coordinate[1]] != ' ');

    (*board)[coordinate[0]][coordinate[1]] = player;
    (*moves)++;
}

// Function for the game loop
void playGame(char ***board, int n, int *moves, int *coordinate, char currentPlayer, const char *filename)
{
    move(board, n, moves, currentPlayer, coordinate);
    printBoard(*board, n);
    writeMoves(*board, n, filename);

    if (checkWin(*board, n, currentPlayer, coordinate, filename) || checkDraw(*moves, n, filename))
        return;

    char nextPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    playGame(board, n, moves, coordinate, nextPlayer, filename);
}
