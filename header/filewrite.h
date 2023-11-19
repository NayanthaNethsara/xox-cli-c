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