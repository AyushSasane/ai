/*
BFS (Breadth-First Search)
Time Complexity   : O(V + E)
Space Complexity  : O(V)
Input Format:
    N M          // number of vertices and edges
    u v          // M lines of undirected edges
    src          // starting vertex
Output Format:
    A single line listing the vertices in the order they are visited by BFS

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
0 1 2 3 4 5 6

Graph Diagram (undirected):
        0
       / \
      1   2
     / \  / \
    3  4 5  6
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N);

    // Read undirected edges
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int src;
    cin >> src;

    vector<bool> vis(N, false);
    queue<int> q;

    // Initialize BFS
    vis[src] = true;
    q.push(src);

    // Perform BFS traversal
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    cout << "\n";

    return 0;
}
