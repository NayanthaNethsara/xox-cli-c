#include <stdio.h>
#include <stdlib.h>

void createBoard(char ***arr, int n);
void printBoard(char **arr, int n);
void clearBoard(char ***arr, int n);
void freeBoard(char ***arr, int n);
void writeMoves(char **arr, int n, FILE *logfile);

void move(char ***arr, int n, int *moves, char player);
int checkWin(char **arr, int n, char player);
int checkDraw(int moves, int n);

int main()
{
    int n, moves = 0;
    char c;
    char **board;

    const char *filename = "output.txt";
    FILE *logfile = fopen(filename, "a");

    if (logfile == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("Enter Board Size: ");
    scanf("%d", &n);

    createBoard(&board, n);
    clearBoard(&board, n);
    printBoard(board, n);
    writeMoves(board, n, logfile);

    while (1)
    {
        move(&board, n, &moves, 'X');
        printBoard(board, n);
        writeMoves(board, n, logfile);
        printf("Move count: %d\n", moves);

        if (checkWin(board, n, 'X'))
            break;
        else if (checkDraw(moves, n))
            break;

        move(&board, n, &moves, 'O');
        printBoard(board, n);
        writeMoves(board, n, logfile);
        printf("Move count: %d\n", moves);

        if (checkWin(board, n, 'O'))
            break;
        else if (checkDraw(moves, n))
            break;
    }

    freeBoard(&board, n);
    fclose(logfile);

    return 0;
}

int checkDraw(int moves, int n)
{
    if (moves >= n * n)
    {
        printf("Draw! No Possible Moves. \n");
        return 1;
    }
    else
        return 0;
}

int checkWin(char **arr, int n, char player)
{
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

    int win(char player)
    {
        printf("Congratulations! %c Win the game.\n", player);
        return 1;
    }

    // Check main diagonal
    if (checkMainDiagonal())
    {
        win(player);
    }

    // Check anti-diagonal
    if (checkAntiDiagonal())
    {
        win(player);
    }

    // Check columns
    for (int col = 0; col < n; col++)
    {
        if (checkColumn(col))
        {
            win(player);
        }
    }

    // Check rows
    for (int row = 0; row < n; row++)
    {
        if (checkRow(row))
        {

            win(player);
        }
    }

    return 0;
}

void createBoard(char ***arr, int n)
{
    *arr = (char **)malloc(n * sizeof(char *));

    for (int i = 0; i < n; i++)
    {
        (*arr)[i] = (char *)malloc(n * sizeof(char));
    }
}

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

void move(char ***arr, int n, int *moves, char player)
{
    char c;
    int coordinate[2];

    printf("Move (%c): ", player);
    scanf("%d%c%d", &coordinate[0], &c, &coordinate[1]);

    if (coordinate[0] >= n || coordinate[1] >= n || coordinate[0] <= -1 || coordinate[1] <= -1 || (*arr)[coordinate[0]][coordinate[1]] != ' ')
    {
        printf("Invalid move, try again \n");
        move(arr, n, moves, player);
    }
    else
    {
        (*arr)[coordinate[0]][coordinate[1]] = player;
        (*moves)++;
    }
}

void freeBoard(char ***arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        free((*arr)[i]);
    }
    free(*arr);
}

void writeMoves(char **arr, int n, FILE *logfile)
{
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
}