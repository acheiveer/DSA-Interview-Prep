/*
A minimum distance of src from every other node present in graph with all non-negative weights (optimized algo) OR Negative weighted a-cyclic graph (Non-optimized Algo)
Complexity for dijktra's Algo -> O((V + E) log V)
E-Edges V-Vertices

We may add same node multiple times, hence total elements in a heap might be E. Hence, log(E).
Intreasting thing is to E = V*(V-1) => 2*log(V).

Slight modification: Think of adding a virtual node which joins an edge to each node. [Similar to multi source BFS]

Dikjtras can be applied 3-4 times... you reverse graph... node a to src and dest dist
https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/description/
*/
#include <bits/stdc++.h>
using namespace std;

const int LIM = 3000;
const int INF = 1e9;

typedef pair<int, int> pii;

vector<pii> adj[LIM];
vector<int> min_dist(LIM, INF);

// Each node in adj list represents vertex and weight
void addEdge(int u, int v, int wt) {
    adj[u].push_back({v, wt});
    adj[v].push_back({u, wt}); // Remove this line if graph is directed
}

void dijkstra(int src) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    min_dist.assign(LIM, INF);

    min_dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int curr_dist = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        if (curr_dist > min_dist[curr])
            continue;

        for (auto u : adj[curr]) {
            int next = u.first;
            int weight = u.second;

            if (min_dist[next] > min_dist[curr] + weight) {
                min_dist[next] = min_dist[curr] + weight;
                pq.push({min_dist[next], next});
            }
        }
    }
}

int main() {
    int V, E, src;

    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    for (int i = 0; i < E; i++) {
        int u, v, wt;
        cout << "Enter vertex u, vertex v and weight: ";
        cin >> u >> v >> wt;
        addEdge(u, v, wt);
    }

    cout << "Enter the source node: ";
    cin >> src;

    dijkstra(src);

    cout << "\nMinimum distances from source node " << src << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "Node " << i << ": ";
        if (min_dist[i] == INF)
            cout << "INF\n";
        else
            cout << min_dist[i] << "\n";
    }

    return 0;
}
