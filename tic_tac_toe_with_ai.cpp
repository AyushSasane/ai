#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

/*
Sample Input Moves:
Enter your name: xxxxx

Moves (row col):
0 0
1 1
0 2
0 1
2 2
*/

// Board and variables
char board[3][3];
string playerName;

void initBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '.';
}

void printBoard() {
    cout << "\nCurrent Board:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << board[i][j] << " ";
        cout << "\n";
    }
    cout << endl;
}

bool checkWin(char p) {
    for (int i = 0; i < 3; i++)
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p) return true;
    for (int j = 0; j < 3; j++)
        if (board[0][j] == p && board[1][j] == p && board[2][j] == p) return true;
    if (board[0][0] == p && board[1][1] == p && board[2][2] == p) return true;
    if (board[0][2] == p && board[1][1] == p && board[2][0] == p) return true;
    return false;
}

bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '.')
                return true;
    return false;
}

bool tryToWinOrBlock(char symbol) {
    for (int i = 0; i < 3; i++) {
        // Rows
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == '.') {
            board[i][2] = 'O';
            return true;
        }
        if (board[i][0] == symbol && board[i][2] == symbol && board[i][1] == '.') {
            board[i][1] = 'O';
            return true;
        }
        if (board[i][1] == symbol && board[i][2] == symbol && board[i][0] == '.') {
            board[i][0] = 'O';
            return true;
        }
        // Columns
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == '.') {
            board[2][i] = 'O';
            return true;
        }
        if (board[0][i] == symbol && board[2][i] == symbol && board[1][i] == '.') {
            board[1][i] = 'O';
            return true;
        }
        if (board[1][i] == symbol && board[2][i] == symbol && board[0][i] == '.') {
            board[0][i] = 'O';
            return true;
        }
    }
    // Diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == '.') {
        board[2][2] = 'O';
        return true;
    }
    if (board[0][0] == symbol && board[2][2] == symbol && board[1][1] == '.') {
        board[1][1] = 'O';
        return true;
    }
    if (board[1][1] == symbol && board[2][2] == symbol && board[0][0] == '.') {
        board[0][0] = 'O';
        return true;
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == '.') {
        board[2][0] = 'O';
        return true;
    }
    if (board[0][2] == symbol && board[2][0] == symbol && board[1][1] == '.') {
        board[1][1] = 'O';
        return true;
    }
    if (board[1][1] == symbol && board[2][0] == symbol && board[0][2] == '.') {
        board[0][2] = 'O';
        return true;
    }
    return false;
}

void computerMove() {
    if (tryToWinOrBlock('O'))
        return;
    if (tryToWinOrBlock('X'))
        return;
    srand(time(0));
    int r, c;
    do {
        r = rand() % 3;
        c = rand() % 3;
    } while (board[r][c] != '.');
    board[r][c] = 'O';
}

void runTicTacToe(istream& inputStream = cin) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Enter your name: ";
    getline(inputStream, playerName);
    cout << "You are 'X'. Computer is 'O'.\n";

    initBoard();
    char player = 'X';
    int moves = 0;

    while (moves < 9) {
        printBoard();
        if (player == 'X') {
            int r, c;
            bool validMove = false;
            while (!validMove) {
                cout << playerName << " (" << player << "), enter your move (row and column: 0 1 2): ";
                if (!(inputStream >> r >> c)) {
                    cout << "No more moves in input. Exiting.\n";
                    return;
                }
                cout << r << " " << c << "\n";

                if (r < 0 || r > 2 || c < 0 || c > 2 || board[r][c] != '.') {
                    cout << "Invalid move. Try again.\n";
                } else {
                    board[r][c] = player;
                    validMove = true;
                }
            }
        } else {
            cout << "Computer's move:\n";
            computerMove();
        }
        moves++;
        if (checkWin(player)) {
            printBoard();
            if (player == 'X')
                cout << playerName << " (" << player << ") wins!\n";
            else
                cout << "Computer (" << player << ") wins!\n";
            return;
        }
        player = (player == 'X') ? 'O' : 'X';
    }
    printBoard();
    cout << "It's a draw!\n";
}

int main() {
    runTicTacToe();
    return 0;
}
