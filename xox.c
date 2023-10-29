#include <stdio.h>
#include <stdlib.h>

void createBoard(char ***arr, int n);
void printBoard(char **arr, int n);
void clearBoard(char ***arr, int n);
void freeBoard(char ***arr, int n);
void writeMoves(char **arr, int n, const char *filename);
void writeFile(char *msg, const char *filename);

void move(char ***arr, int n, int *moves, char player);
int checkWin(char **arr, int n, char player, const char *filename);
int checkDraw(int moves, int n, const char *filename);

int main()
{
    int n, moves = 0;
    char c;
    char **board;

    const char *filename = "output.txt";

    while (1)
    {
        printf("Enter Board Size: ");
        scanf("%d", &n);

        if (n >= 3)
        {
            break;
        }
        else
        {
            printf("Enter Valid Board Size: (>=3) ");
            scanf("%d", &n);
        }
    }

    char msg[50];
    sprintf(msg, "Board Size is: %d", n);
    writeFile(msg, filename);

    createBoard(&board, n);
    clearBoard(&board, n);
    printBoard(board, n);
    writeMoves(board, n, filename);

    while (1)
    {
        move(&board, n, &moves, 'X');
        printBoard(board, n);
        writeMoves(board, n, filename);

        if (checkWin(board, n, 'X', filename))
            break;
        else if (checkDraw(moves, n, filename))
            break;

        move(&board, n, &moves, 'O');
        printBoard(board, n);
        writeMoves(board, n, filename);

        if (checkWin(board, n, 'O', filename))
            break;
        else if (checkDraw(moves, n, filename))
            break;
    }

    freeBoard(&board, n);

    return 0;
}

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

int checkWin(char **arr, int n, char player, const char *filename)
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

void writeMoves(char **arr, int n, const char *filename)
{
    FILE *logfile = fopen(filename, "a");

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

void writeFile(char *msg, const char *filename)
{
    FILE *logfile = fopen(filename, "a");

    if (logfile == NULL)
    {
        printf("Error opening the file.\n");
    }

    fprintf(logfile, "%s\n", msg);

    fclose(logfile);
}