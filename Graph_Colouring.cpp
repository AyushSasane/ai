/*
Graph Colouring (m‑Coloring Problem)

Time Complexity   : O(m^N) in the worst case (tries all color assignments)  
Space Complexity  : O(N + E) (for recursion stack plus adjacency list)  

Input Format:
    N M           // number of vertices and edges
    u v           // M lines of undirected edges between u and v
    m             // number of colors

Sample Input:
    10 12
    0 1
    0 2
    1 3
    1 4
    2 5
    2 6
    3 7
    4 7
    5 8
    6 8
    7 9
    8 9
    3

Sample Output:
    Coloring possible with 3 colors:
    Vertex 0 → Color 1
    Vertex 1 → Color 2
    Vertex 2 → Color 2
    Vertex 3 → Color 3
    Vertex 4 → Color 1
    Vertex 5 → Color 1
    Vertex 6 → Color 3
    Vertex 7 → Color 2
    Vertex 8 → Color 2
    Vertex 9 → Color 1
Graph Diagram (undirected):




        0
       / \
      1   2
     / \  / \
    3   4   5
    |   |   |
    7   7   8
     \ /     \
     9        9
      \      /
        8–––
        
Explanation:
  1. We try to assign one of m colors to each of the 10 vertices so that no two adjacent vertices share the same color.  
  2. We use backtracking: assign a color to vertex 0, recurse through 1, 2, …, 9, and backtrack on conflicts.
*/

#include <bits/stdc++.h>
using namespace std;

int N, M, mColors;
vector<vector<int>> adj;
vector<int> color;

// Check if it’s safe to color vertex u with c
bool isSafe(int u, int c) {
    for (int v : adj[u]) {
        if (color[v] == c) return false;
    }
    return true;
}

// Backtracking utility to color vertex u and onward
bool graphColoring(int u) {
    if (u == N) return true;               // All vertices colored
    for (int c = 1; c <= mColors; c++) {
        if (isSafe(u, c)) {
            color[u] = c;
            if (graphColoring(u + 1)) return true;
            color[u] = 0;                  // backtrack
        }
    }
    return false;                          // no valid color found
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    adj.assign(N, {});
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> mColors;

    color.assign(N, 0);
    if (graphColoring(0)) {
        cout << "Coloring possible with " << mColors << " colors:\n";
        for (int i = 0; i < N; i++) {
            cout << "Vertex " << i << " -----> Color " << color[i] << "\n";
        }
    } else {
        cout << "No valid coloring with " << mColors << " colors.\n";
    }

    return 0;
}
