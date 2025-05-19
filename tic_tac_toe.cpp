#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int ROWS = 6;
const int COLS = 7;

vector<vector<char>> board(ROWS, vector<char>(COLS, ' '));
vector<int> moves;
int moveIndex = 0;

void printBoard() {
    cout << "\n  0 1 2 3 4 5 6 \n";
    cout << " ---------------\n";
    for (int row = 0; row < ROWS; ++row) {
        cout << "|";
        for (int col = 0; col < COLS; ++col) {
            cout << board[row][col] << "|";
        }
        cout << "\n ---------------\n";
    }
    cout << "  0 1 2 3 4 5 6 \n";
}

bool isValidColumn(int col) {
    return col >= 0 && col < COLS && board[0][col] == ' ';
}

bool makeMove(int col, char player) {
    if (!isValidColumn(col)) return false;
    for (int row = ROWS - 1; row >= 0; --row) {
        if (board[row][col] == ' ') {
            board[row][col] = player;
            return true;
        }
    }
    return false;
}

bool checkDirection(int row, int col, int dRow, int dCol, char player) {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        int r = row + i * dRow;
        int c = col + i * dCol;
        if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player) {
            count++;
        }
    }
    return count == 4;
}

bool checkWin(char player) {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (board[row][col] == player) {
                if (checkDirection(row, col, 0, 1, player) || // Horizontal
                    checkDirection(row, col, 1, 0, player) || // Vertical
                    checkDirection(row, col, 1, 1, player) || // Diagonal ↘
                    checkDirection(row, col, 1, -1, player))  // Diagonal ↙
                    return true;
            }
        }
    }
    return false;
}

bool isBoardFull() {
    for (int col = 0; col < COLS; ++col) {
        if (board[0][col] == ' ') return false;
    }
    return true;
}

int readMove() {
    if (moveIndex >= moves.size()) return -1;
    return moves[moveIndex++];
}

int main() {
    cout << "Welcome to Connect 4!\n";
    cout << "🟥 Red = R, ⬛ Black = B\n";

    /*
     * How to input moves:
     * Enter column numbers (0 to 6) separated by spaces or new lines.
     * For example:
     * 3 3 0 6 2 2 4
     * 
     * Each number represents the column where the current player
     * drops their piece. The players alternate automatically (R then B).
     * 
     * End input with EOF (Ctrl+D in Linux/Mac, Ctrl+Z in Windows) to start the game.
     */

    int input;
    while (cin >> input) {
        moves.push_back(input);
    }

    char currentPlayer = 'R';
    printBoard();

    while (true) {
        int col = readMove();
        if (col == -1) {
            cout << "No more moves provided. Game over.\n";
            break;
        }

        cout << "\nPlayer " << currentPlayer << " played column " << col << "\n";
        if (!makeMove(col, currentPlayer)) {
            cout << "Invalid move. Skipping turn.\n";
        } else {
            printBoard();
            if (checkWin(currentPlayer)) {
                cout << "Player " << currentPlayer << " wins!\n";
                break;
            }
            if (isBoardFull()) {
                cout << "It's a tie!\n";
                break;
            }
            currentPlayer = (currentPlayer == 'R') ? 'B' : 'R';
        }
    }

    return 0;
}
