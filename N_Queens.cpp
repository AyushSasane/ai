/*
N-Queens Problem (All Solutions via Backtracking)

Time Complexity   : O(K·N!) in the worst case, where K is the cost per solution (printing/storing all): backtracking explores permutations :contentReference[oaicite:0]{index=0}  
Space Complexity  : O(N^2 + S·N^2), for the board matrix, recursion stack, and storage of S solutions each of size N×N :contentReference[oaicite:1]{index=1}  

Input Format:
    N             // size of the chessboard and number of queens

Output Format:
    All distinct solutions printed as N×N boards with ‘Q’ and ‘.’  
    Then a final line: “Total solutions: S (optimal)”
Sample Input:
    4
Sample Output:
    Solution #1:
    . Q . .
    . . . Q
    Q . . .
    . . Q .

    Solution #2:
    . . Q .
    Q . . .
    . . . Q
    . Q . .

    Total solutions: 2 (optimal)

Explanation:
  1. Backtrack row by row, trying each column and checking column/diagonal safety.  
  2. Collect and print every distinct arrangement, then report the total count.  
*/

#include <bits/stdc++.h>
using namespace std;

// Check if it's safe to place a queen at (row, col)
bool isSafe(const vector<int> &pos, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (pos[i] == col || abs(pos[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

// Backtracking to generate all solutions
void solveAll(int row, int N, vector<int> &pos, vector<vector<int>> &solutions) {
    if (row == N) {
        solutions.push_back(pos);
        return;
    }
    for (int col = 0; col < N; col++) {
        if (isSafe(pos, row, col)) {
            pos[row] = col;
            solveAll(row + 1, N, pos, solutions);
            // backtrack: pos[row] will be overwritten
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> pos(N, -1);
    vector<vector<int>> solutions;
    solveAll(0, N, pos, solutions);

    // Print each solution
    for (int k = 0; k < (int)solutions.size(); k++) {
        cout << "Solution #" << (k + 1) << ":\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << (solutions[k][i] == j ? 'Q' : '.') << ' ';
            }
            cout << "\n";
        }
        cout << "\n";
    }

    // Final optimality statement
    cout << "Total solutions: " << solutions.size() << " (optimal)\n";

    return 0;
}
