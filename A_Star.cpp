/*
A* Algorithm with Euclidean distance heuristic

Time Complexity   : O((V + E) log V)          // priority queue operations dominate
Space Complexity  : O(V)                      // dist, parent, and adjacency storage

Input Format:
    N M                               // number of nodes and edges
    x0 y0                            // coordinates of node 0
    x1 y1                            // coordinates of node 1
    ...
    xN-1 yN-1                       // coordinates of node N-1
    u v w                           // M lines of directed edges: from u to v with weight w
    start goal                     // start and goal node indices

Sample Input:
6 7
0 0
1 0
0 1
2 0
1 1
2 1
0 1 2
0 2 4
1 2 1
1 3 7
2 4 3
3 5 1
4 5 5
0 5

Sample Output:
Cost: 10
Path: 0 1 3 5

Graph diagram (nodes with coordinates in 2D space):

      (0)(0,0)
       /      \
  2 /          \ 4
   /            \
 (1)(1,0)     (2)(0,1)
   | \           \
  7|  \1          \3
   v   v           v
 (3)(2,0) --      (4)(1,1)
   |               |
  1|               |5
   v               v
 (5)(2,1)

Explanation:
1. Start from 'start' node, estimate distance to goal using Euclidean heuristic.
2. Use priority queue ordered by f = g + h to guide search efficiently.
3. Stops when the goal node is reached or no path exists.
*/

#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

struct Node {
    int x, y;
};

// Euclidean distance heuristic between two nodes
double heuristic(const Node& a, const Node& b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

void runAstar() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // Read coordinates for each node
    vector<Node> nodes(N);
    for (int i = 0; i < N; i++) {
        cin >> nodes[i].x >> nodes[i].y;
    }

    // Read directed weighted edges into adjacency list
    vector<vector<pii>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    // Read start and goal nodes
    int start, goal;
    cin >> start >> goal;

    const double INF = 1e15;
    vector<double> dist(N, INF);
    vector<int> parent(N, -1);

    // Min-heap priority queue ordered by f = g + h
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> pq;

    // Initialize distance for start node and push into queue
    dist[start] = 0;
    double h_start = heuristic(nodes[start], nodes[goal]);
    pq.emplace(dist[start] + h_start, start);

    while (!pq.empty()) {
        auto [f, u] = pq.top(); pq.pop();

        // If reached goal, stop
        if (u == goal) break;

        // If this entry is outdated, skip
        if (f - heuristic(nodes[u], nodes[goal]) > dist[u] + 1e-9) continue;

        // Relax edges
        for (auto& [v, w] : adj[u]) {
            double g2 = dist[u] + w;  // cost to neighbor
            if (g2 < dist[v]) {
                dist[v] = g2;
                parent[v] = u;
                double f2 = g2 + heuristic(nodes[v], nodes[goal]);
                pq.emplace(f2, v);
            }
        }
    }

    if (dist[goal] == INF) {
        cout << "No path\n";
    } else {
        cout << "Cost: " << dist[goal] << "\n";
        cout << "Path:";
        vector<int> path;
        for (int v = goal; v != -1; v = parent[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        for (int x : path)
            cout << " " << x;
        cout << "\n";
    }
}

int main() {
    runAstar();
    return 0;
}
