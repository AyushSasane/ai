/*
AO* Algorithm (AND-OR Search)

Time Complexity   : Exponential (O(b^d) worst-case, where b = branching factor, d = depth)
Space Complexity  : Exponential (stores partial solution graphs and recursion stack)

Input Format:
    N M                      // Number of nodes and number of edges

    u v c t                  // M lines: edge from node `u` to `v` with cost `c`
                             // t = 1 if it's an AND-edge, t = 0 for OR-edge

    start goal              // Starting and goal node

Sample Input:
    5 6
    0 1 2 0                // OR-edge: 0 → 1 (cost 2)
    0 2 3 1                // AND-edge: 0 → 2 (cost 3)
    1 3 4 0                // OR-edge: 1 → 3 (cost 4)
    1 4 1 1                // AND-edge: 1 → 4 (cost 1)
    2 4 2 0                // OR-edge: 2 → 4 (cost 2)
    4 3 1 0                // OR-edge: 4 → 3 (cost 1)
    0 3                   // Start node = 0, Goal node = 3

input-    
5 6
0 1 2 0
0 2 3 1
1 3 4 0
1 4 1 1
2 4 2 0
4 3 1 0
0 3    

Sample Output:
    Cost: 3
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;       // successor node
    int cost;     // edge cost
    bool isAnd;   // true if AND-edge, false if OR-edge
};

const int INF = 1e9;

int N, M, startNode, goalNode;
vector<vector<Edge>> graph_;
vector<int> solved, valueMemo;

// AO* search function: returns minimal cost to solve `node`
int ao_star(int node) {
    if (node == goalNode) {
        return valueMemo[node] = 0;
    }
    if (solved[node]) {
        return valueMemo[node];
    }
    int bestCost = INF;

    for (auto &e : graph_[node]) {
        int childCost = ao_star(e.to);
        int totalCost = childCost + e.cost;
        bestCost = min(bestCost, totalCost);
    }

    solved[node] = 1;
    return valueMemo[node] = bestCost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read number of nodes and edges
    cin >> N >> M;
    graph_.assign(N, {});
    
    // Read edges: u v cost type (AND = 1, OR = 0)
    for (int i = 0; i < M; i++) {
        int u, v, c, t;
        cin >> u >> v >> c >> t;
        graph_[u].push_back({v, c, t == 1});
    }

    // Read start and goal nodes
    cin >> startNode >> goalNode;

    // Initialize visited and memoization arrays
    solved.assign(N, 0);
    valueMemo.assign(N, INF);

    // Run AO* algorithm
    int result = ao_star(startNode);
    if (result >= INF) {
        cout << "No solution\n";
    } else {
        cout << "Cost: " << result << "\n";
    }

    return 0;
}
