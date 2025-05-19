/*
DFS (Depth-First Search)

Time Complexity   : O(V + E)               // visits each vertex and edge once
Space Complexity  : O(V)                   // recursion stack + visited array

Input Format:
    N M                      // number of vertices and edges
    u v                      // M lines of undirected edges
    src                      // starting vertex for DFS

Sample Input:
    7 6
    0 1
    0 2
    1 3
    1 4
    2 5
    2 6
    0

Sample Output:
    0 1 3 4 2 5 6

Graph Diagram (undirected):

        0
       / \
      1   2
     / \  / \
    3  4 5  6
*/

#include <bits/stdc++.h>
using namespace std;

int N, M, src;
vector<vector<int>> adj;
vector<bool> visited;

void dfs(int u) {
    visited[u] = true;
    cout << u << " ";
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Read number of vertices and edges
    cin >> N >> M;
    adj.assign(N, {});
    
    // Read edges (undirected)
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Read starting vertex for DFS
    cin >> src;

    // Initialize visited array
    visited.assign(N, false);

    // Perform DFS from source
    dfs(src);
    cout << "\n";

    return 0;
}
