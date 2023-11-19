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
int checkWin(char **board, int n, char player, int lastMove[2], const char *filename)
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
    if (lastMove[0] == lastMove[1])
    {

        if (checkMainDiagonal())
        {
            return win(player, filename);
        }
    }
    // Check anti-diagonal
    else if (lastMove[0] == n - 1 - lastMove[1])
    {

        if (checkAntiDiagonal())
        {
            return win(player, filename);
        }
    }

    // Check columns
    if (checkColumn(lastMove[1]))
    {
        return win(player, filename);
    }

    // Check rows
    if (checkRow(lastMove[0]))
    {

        return win(player, filename);
    }

    return 0;
}

// Function for a player to make a move
void move(char ***board, int n, int *moves, char player, int *coordinate)
{
    char c;

    // Get a move
    do
    {
        printf("Move (%c): ", player);
        scanf("%d%c%d", &coordinate[0], &c, &coordinate[1]);

    } while (coordinate[0] >= n || coordinate[1] >= n || coordinate[0] <= -1 || coordinate[1] <= -1 || (*board)[coordinate[0]][coordinate[1]] != ' '); // Validate the move

    // Place the move
    (*board)[coordinate[0]][coordinate[1]] = player;
    // Count moves
    (*moves)++;
}

// Function for a game loop
void playGame(char ***board, int n, int *moves, int *coordinate, char currentPlayer, const char *filename)
{
    // Player makes a move
    move(board, n, moves, currentPlayer, coordinate);
    printBoard(*board, n);
    writeMoves(*board, n, filename);

    // Check if the current player has won or if it's a draw
    if (checkWin(*board, n, currentPlayer, coordinate, filename) || checkDraw(*moves, n, filename))
    {
        return; // Game over
    }

    // Switch to the next player
    char nextPlayer = (currentPlayer == 'X') ? 'O' : 'X';

    // Recursively call playGame for the next player's turn
    playGame(board, n, moves, coordinate, nextPlayer, filename);
}
