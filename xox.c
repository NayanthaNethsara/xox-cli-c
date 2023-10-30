#include <stdio.h>
#include <stdlib.h>

// Function prototypes for board
void getBoardSize(int *n);
void createBoard(char ***arr, int n);
void printBoard(char **arr, int n);
void clearBoard(char ***arr, int n);
void freeBoard(char ***arr, int n);

// Function prototypes for file handling
void writeMoves(char **arr, int n, const char *filename);
void writeFile(char *msg, const char *filename);

// Function prototypes for gameplay
void move(char ***arr, int n, int *moves, char player);
int checkWin(char **arr, int n, char player, const char *filename);
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
    while (1)
    {
        // Player 'X' makes a move
        move(&board, n, &moves, 'X');
        printBoard(board, n);
        writeMoves(board, n, filename);

        // Check if 'X' has won or if it's a draw
        if (checkWin(board, n, 'X', filename))
            break;
        else if (checkDraw(moves, n, filename))
            break;

        // Player 'O' makes a move
        move(&board, n, &moves, 'O');
        printBoard(board, n);
        writeMoves(board, n, filename);

        // Check if 'O' has won or if it's a draw
        if (checkWin(board, n, 'O', filename))
            break;
        else if (checkDraw(moves, n, filename))
            break;
    }

    // Free memory used by the board
    freeBoard(&board, n);

    return 0;
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
int checkWin(char **arr, int n, char player, const char *filename)
{
    // Function to check the main diagonal
    int checkMainDiagonal()
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i][i] != player)
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
            if (arr[i][n - 1 - i] != player)
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
            if (arr[i][col] != player)
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
            if (arr[row][i] != player)
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
void createBoard(char ***arr, int n)
{
    *arr = (char **)malloc(n * sizeof(char *));

    for (int i = 0; i < n; i++)
    {
        (*arr)[i] = (char *)malloc(n * sizeof(char));
    }
}

// Function to print the game board
void printBoard(char **arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c", arr[i][j]);
            if (j != n - 1)
            {
                printf(" | ");
            }
        }
        printf("\n");
    }
}

// Function to clear the game board
void clearBoard(char ***arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            (*arr)[i][j] = ' ';
        }
    }
}

// Function for a player to make a move
void move(char ***arr, int n, int *moves, char player)
{
    char c;
    int coordinate[2];

    // Get a move
    printf("Move (%c): ", player);
    scanf("%d%c%d", &coordinate[0], &c, &coordinate[1]);

    // Validate the move
    if (coordinate[0] >= n || coordinate[1] >= n || coordinate[0] <= -1 || coordinate[1] <= -1 || (*arr)[coordinate[0]][coordinate[1]] != ' ')
    {
        printf("Invalid move, try again \n");
        move(arr, n, moves, player);
    }
    else
    {
        // Place the move
        (*arr)[coordinate[0]][coordinate[1]] = player;
        // Count moves
        (*moves)++;
    }
}

// Function to free memory used by the board
void freeBoard(char ***arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        // Free Row
        free((*arr)[i]);
    }
    free(*arr);
}

// Function to write the game board to a file
void writeMoves(char **arr, int n, const char *filename)
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
            fprintf(logfile, "%c", arr[i][j]);
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