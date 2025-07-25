
/*************************** Implementation *****************************/


// 1. Depth-First Search (DFS)
/******************************************** 
--> The Graph class contains:
 1. An adjList that maps each node to its neighbors.
 2. A public method dfsTraversal which initializes the visited set and starts the DFS.
 3. A recursive helper function dfs() that:
    a. Marks the current node as visited
    b. Recursively visits all unvisited neighbors

---> Uses unordered_set<int> for constant-time lookup during visited checks.*/
#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> adjList;
public:
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        // Uncomment below if the graph is undirected
        // adjList[v].push_back(u);
    }

    void dfs(int start, unordered_set<int>& visited) {
        visited.insert(start);
        cout << start << " ";

        for (int neighbor : adjList[start]) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(neighbor, visited);
            }
        }
    }

    void dfsTraversal(int start) {
        unordered_set<int> visited;
        dfs(start, visited);
    }
};


// 2. Breadth-First Search (BFS)
/******************************************** 
--> Queue-based Traversal:
    -> Uses a queue to process nodes in breadth-wise (level-order) fashion.
--> Visited Tracking:
    -> unordered_set ensures each node is visited only once.
--> Adjacency List:
    -> Efficient for sparse graphs and common use cases.*/
#include <bits/stdc++.h>
using namespace std;
class Graph {
private:
    unordered_map<int, vector<int>> adjList;
public:
    // Add edge to the graph
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        // Uncomment if the graph is undirected
        // adjList[v].push_back(u);
    }

    // Breadth-First Search
    void bfs(int start) {
        unordered_set<int> visited;
        queue<int> q;

        visited.insert(start);
        q.push(start);

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            cout << vertex << " ";

            for (int neighbor : adjList[vertex]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }
};



// 3. Dijkstra's Shortest Path
/******************************************** 
--> Dijkstra’s Shortest Path Algorithm using a priority queue (min-heap) with an adjacency list (with weights)
--> Data Structures Used:
    -> unordered_map<int, vector<pair<int, int>>> for storing weighted graph.
    -> priority_queue for selecting the node with the smallest known distance.
-->Initialization:
    -> All node distances are initialized to INT_MAX (infinity).
--> Relaxation:
    -> If a shorter path is found, the distance is updated and the new value is pushed into the priority queue.
    
---> Where is Dijkstra’s Algorithm used?
Problem / Scenario	                                Why Dijkstra is Used
Shortest Path in Weighted Graph	              Computes minimum distance from source to all nodes.
GPS Navigation / Routing Systems	          Finds the quickest route on road networks.
Network Packet Routing	                      Ensures data follows the least-cost path.
AI Pathfinding (Games, Maps)	              Computes optimal paths for movement or decision-making.
Minimum Cost to Destination	                  Used where edge costs are involved in reaching the target node.
Delay Optimization in Circuits	              Useful in circuit simulation for timing optimization.
Flight Scheduling (Cheapest Flights)	      Graph of cities and ticket prices — optimize cost path.*/
#include <bits/stdc++.h>
using namespace std;
class Graph {
private:
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list: {vertex, weight}   
public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }
    
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // For undirected graph
    }
    
    vector<int> dijkstra(int src) {
        // Priority queue: {distance, vertex}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        vector<int> dist(V, INT_MAX);
        vector<bool> visited(V, false);
        
        dist[src] = 0;
        pq.push({0, src});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            // Check all neighbors of u
            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                // Relaxation step
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
};



// 4. Topological Sort
/******************************************** 
--> Topological Sort is a linear ordering of vertices such that for every directed edge u → v, vertex u comes before v.
--> Implemented using DFS + stack:
    -> Visit all unvisited neighbors first (postorder traversal).
    -> Push vertex to stack once all its dependencies are resolved.

    
---> Where is Topological Sort used?
Use Case / DSA Problem Type	                   Why Topological Sort is Useful
Task Scheduling / Build Systems	           Helps determine correct order of task execution with dependencies.
Course Prerequisite Problems	          Identify if it’s possible to take all courses in order.
Dependency Resolution in Compilers	     Determines compilation order for source files.
Deadlock Detection (in systems)	         Circular dependencies show no valid topological order.
Directed Acyclic Graph (DAG) problems	  Any linear ordering problem in a DAG relies on topological sort.
*/
#include <bits/stdc++.h>
using namespace std;
class Graph {
private:
    unordered_map<int, vector<int>> adjList;

public:
    // Add edge (directed graph)
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        // Don't add adjList[v].push_back(u); since it's a directed graph
    }
    // DFS helper for topological sort
    void dfs(int vertex, unordered_set<int>& visited, stack<int>& st) {
        visited.insert(vertex);

        for (int neighbor : adjList[vertex]) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(neighbor, visited, st);
            }
        }

        st.push(vertex); // Add to result after all children are processed
    }
    // Topological sort
    vector<int> topologicalSort() {
        unordered_set<int> visited;
        stack<int> st;
        vector<int> result;

        for (auto it = adjList.begin(); it != adjList.end(); ++it) {
            int vertex = it->first;
            if (visited.find(vertex) == visited.end()) {
                dfs(vertex, visited, st);
            }
        }
        while (!st.empty()) {
            result.push_back(st.top());
            st.pop();
        }
        return result;
    }
};


// ----> Topological Sort using BFS (Kahn's Algorithm)
#include <bits/stdc++.h>
using namespace std;

// Function to return topological sort order using BFS (Kahn's Algorithm)
vector<int> topoSortBFS(int V, vector<int> adj[]) {
    vector<int> indegree(V, 0);
    
    // Calculate indegree of each vertex
    for (int i = 0; i < V; i++) {
        for (int neighbor : adj[i]) {
            indegree[neighbor]++;
        }
    }
    queue<int> q;
    // Enqueue vertices with indegree 0
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> topoOrder;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);
        
        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    // If topoOrder does not contain all vertices, graph has a cycle
    if (topoOrder.size() != V) {
        cout << "Graph contains a cycle!\n";
        return {};
    }
    
    return topoOrder;
}



// 5. Union-Find (Disjoint Set)
/******************************************** 
--> Union-Find (Disjoint Set Union - DSU) data structure with Path Compression and Union by Rank
--> find(x): Recursively finds the root of x, and compresses the path by updating the parent of each visited node directly to the root.
--> unionSets(x, y): Combines the sets containing x and y using rank to keep trees shallow.

    
---> Where is Union-Find used?
Problem / Use Case	                                 Why Union-Find is Useful
Cycle Detection in Undirected Graph	          Efficiently checks if two nodes are already connected.
Kruskal's Minimum Spanning Tree (MST)	      Keeps track of connected components while adding edges.
Connected Components (Offline Queries)	      Used to group elements and answer queries efficiently.
Dynamic Connectivity / Network Management	  Handles real-time merging of nodes in disjoint sets.
Image Processing / Segmentation	              Identifies distinct regions (connected components).
Percolation Problems	                      Models flow through porous material using connectivity. */
#include <bits/stdc++.h>
using namespace std;
class UnionFind {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
public:
    // Constructor: initialize each node as its own parent
    UnionFind(const vector<int>& vertices) {
        for (int v : vertices) {
            parent[v] = v;
            rank[v] = 0;
        }
    }
    // Find with path compression
    int find(int item) {
        if (parent[item] != item) {
            parent[item] = find(parent[item]); // Path compression
        }
        return parent[item];
    }
    // Union by rank
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                swap(rootX, rootY);
            }
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY]) {
                rank[rootX]++;
            }
        }
    }
};
