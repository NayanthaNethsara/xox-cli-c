#include <stdio.h>
#include <stdlib.h>

// Function prototypes for board
void getBoardSize(int *n);
void createBoard(char ***board, int n);
void printBoard(char **board, int n);
void clearBoard(char ***board, int n);
void freeBoard(char ***board, int n);

// Function prototypes for file handling
void writeMoves(char **board, int n, const char *filename);
void writeFile(char *msg, const char *filename);

// Function prototypes for gameplay
void playGame(char ***board, int n, int *moves, char currentPlayer, const char *filename);
void move(char ***board, int n, int *moves, char player);
int checkWin(char **board, int n, char player, const char *filename);
int checkDraw(int moves, int n, const char *filename);

int main()
{
    int n, moves = 0;
    char **board;
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
    playGame(&board, n, &moves, 'X', filename);

    // Free memory used by the board
    freeBoard(&board, n);

    return 0;
}

void playGame(char ***board, int n, int *moves, char currentPlayer, const char *filename)
{
    // Player makes a move
    move(board, n, moves, currentPlayer);
    printBoard(*board, n);
    writeMoves(*board, n, filename);

    // Check if the current player has won or if it's a draw
    if (checkWin(*board, n, currentPlayer, filename) || checkDraw(*moves, n, filename))
    {
        return; // Game over
    }

    // Switch to the next player
    char nextPlayer = (currentPlayer == 'X') ? 'O' : 'X';

    // Recursively call playGame for the next player's turn
    playGame(board, n, moves, nextPlayer, filename);
}

// Function to get a valid board size (n should be >= 3)
void getBoardSize(int *n)
{
    printf("Enter Board Size: ");
    scanf("%d", n);

    if ((*n) < 3)
    {
        printf("Invalid board size, board size should be (>=3) \n");
        getBoardSize(n);
    }
}

// Function to check for a draw
int checkDraw(int moves, int n, const char *filename)
{
    if (moves >= n * n)
    {
        char *msg = "Draw! No Possible Moves. \n";
        printf("%s", msg);
        writeFile(msg, filename);
        return 1;
    }
    else
        return 0;
}

// Function to check for a Win
int checkWin(char **board, int n, char player, const char *filename)
{
    // Function to check the main diagonal
    int checkMainDiagonal()
    {
        for (int i = 0; i < n; i++)
        {
            if (board[i][i] != player)
            {
                return 0;
            }
        }
        return 1;
    }

    // Function to check the anti diagonal
    int checkAntiDiagonal()
    {
        for (int i = 0; i < n; i++)
        {
            if (board[i][n - 1 - i] != player)
            {
                return 0;
            }
        }
        return 1;
    }

    // Function to check a column
    int checkColumn(int col)
    {
        for (int i = 0; i < n; i++)
        {
            if (board[i][col] != player)
            {
                return 0;
            }
        }
        return 1;
    }

    // Function to check a row
    int checkRow(int row)
    {
        for (int i = 0; i < n; i++)
        {
            if (board[row][i] != player)
            {
                return 0;
            }
        }
        return 1;
    }

    // Function to print win msg
    int win(char player, const char *filename)
    {

        char msg[50];
        sprintf(msg, "Congratulations! %c Win the game.\n", player);

        printf("%s", msg);
        writeFile(msg, filename);
        return 1;
    }

    // Check main diagonal
    if (checkMainDiagonal())
    {
        return win(player, filename);
    }

    // Check anti-diagonal
    if (checkAntiDiagonal())
    {
        return win(player, filename);
    }

    // Check columns
    for (int col = 0; col < n; col++)
    {
        if (checkColumn(col))
        {
            return win(player, filename);
        }
    }

    // Check rows
    for (int row = 0; row < n; row++)
    {
        if (checkRow(row))
        {

            return win(player, filename);
        }
    }

    return 0;
}

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

// Function for a player to make a move
void move(char ***board, int n, int *moves, char player)
{
    char c;
    int coordinate[2];

    // Get a move
    printf("Move (%c): ", player);
    scanf("%d%c%d", &coordinate[0], &c, &coordinate[1]);

    // Validate the move
    if (coordinate[0] >= n || coordinate[1] >= n || coordinate[0] <= -1 || coordinate[1] <= -1 || (*board)[coordinate[0]][coordinate[1]] != ' ')
    {
        printf("Invalid move, try again \n");
        move(board, n, moves, player);
    }
    else
    {
        // Place the move
        (*board)[coordinate[0]][coordinate[1]] = player;
        // Count moves
        (*moves)++;
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

// Function to write the game board to a file
void writeMoves(char **board, int n, const char *filename)
{
    FILE *logfile = fopen(filename, "a");

    // Check file
    if (logfile == NULL)
    {
        printf("Error opening the file.\n");
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(logfile, "%c", board[i][j]);
            if (j != n - 1)
            {
                fprintf(logfile, " | ");
            }
        }
        fprintf(logfile, "\n");
    }
    fprintf(logfile, "\n");

    fclose(logfile);
}

// Function to write a message to a file
void writeFile(char *msg, const char *filename)
{
    FILE *logfile = fopen(filename, "a");

    // Check file
    if (logfile == NULL)
    {
        printf("Error opening the file.\n");
    }

    fprintf(logfile, "%s\n", msg);

    fclose(logfile);
}