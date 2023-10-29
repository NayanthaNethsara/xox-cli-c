#include <stdio.h>
#include <stdlib.h>

char **createBoard(int n);
void printBoard(char **arr, int n);
void clearBoard(char ***arr, int n);
void freeBoard(char ***arr, int n);
void writeMoves(char **arr, int n, const char *filename);

int main()
{
    int n;
    char **board;

    printf("Enter Board Size: ");
    scanf("%d", &n);

    board = createBoard(n);
    clearBoard(&board, n);
    printBoard(board, n);
    writeMoves(board, n, "Moves/output.txt");
    freeBoard(&board, n);
}

char **createBoard(int n)
{
    char **arr = (char **)malloc(n * sizeof(char *));

    for (int i = 0; i < n; i++)
    {
        arr[i] = (char *)malloc(n * sizeof(char));
    }

    return arr;
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
            (*arr)[i][j] = 'x';
        }
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
    FILE *file = fopen(filename, "a");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(file, "%c", arr[i][j]);
            if (j != n - 1)
            {
                fprintf(file, " | ");
            }
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    fclose(file);
}