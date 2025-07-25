
/*************************** Common Patterns *****************************/


// 1. Cycle Detection
/********************************************/

// a. Cycle Detection in a Directed Graph (Using DFS and Recursion Stack)
//     The approach is to track nodes currently in the recursion stack during DFS traversal. 
//     If you reach a node that is already in the recursion stack, a cycle exists.
#include <bits/stdc++.h>
using namespace std;

// Utility function to detect cycle in directed graph with DFS
bool isCyclicUtil(int u, vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &recStack) {
    if (recStack[u]) // Node is in recursion stack => cycle found
        return true;
    if (visited[u])  // Already visited and not in recursion stack => no cycle here
        return false;

    visited[u] = true;
    recStack[u] = true;

    for (int v : adj[u]) {
        if (isCyclicUtil(v, adj, visited, recStack))
            return true;
    }

    recStack[u] = false; // Backtrack: remove from recursion stack
    return false;
}

// Function to check if a directed graph contains a cycle
bool isCyclic(int V, vector<vector<int>> &edges) {
    vector<vector<int>> adj(V);
    for (auto &e : edges) {
        adj[e[0]].push_back(e[1]); // Directed edge from e[0] to e[1]
    }

    vector<bool> visited(V, false), recStack(V, false);
    for (int i = 0; i < V; i++) {
        if (!visited[i] && isCyclicUtil(i, adj, visited, recStack))
            return true;
    }
    return false;
}

int main() {
    int V = 4;
    vector<vector<int>> edges = {{0,1}, {0,2}, {1,2}, {2,0}, {2,3}}; // Contains cycle(0->2->0)

    cout << (isCyclic(V, edges) ? "Cycle Detected\n" : "No Cycle\n");
    return 0;
}


// b. Cycle Detection in an Undirected Graph (Using DFS and Parent Tracking)
//     The approach is to do DFS and check if an adjacent vertex is visited and is not the parent of the current vertex; if so, a cycle is found.
#include <bits/stdc++.h>
using namespace std;

// Utility function to detect cycle in undirected graph with DFS
bool isCyclicUtil(int u, int parent, vector<vector<int>> &adj, vector<bool> &visited) {
    visited[u] = true;

    for (int v : adj[u]) {
        // If not visited, recur for it
        if (!visited[v]) {
            if (isCyclicUtil(v, u, adj, visited))
                return true;
        }
        // If visited and not parent of current vertex, cycle found
        else if (v != parent) {
            return true;
        }
    }
    return false;
}

// Function to check for cycle in an undirected graph
bool isCyclic(int V, vector<vector<int>> &edges) {
    vector<vector<int>> adj(V);
    for (auto &e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]); // Undirected edge
    }

    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(i, -1, adj, visited))
                return true;
        }
    }
    return false;
}

int main() {
    int V = 5;
    vector<vector<int>> edges = {{0,1}, {1,2}, {2,3}, {3,4}, {4,1}}; // Contains cycle (1-2-3-4-1)

    cout << (isCyclic(V, edges) ? "Cycle Detected\n" : "No Cycle\n");
    return 0;
}



// ******---> Both algorithms run in O(V + E) time, where V = number of vertices and E = number of edges.




// 2. Cycle Detection
/*******************************************
---> Uses unordered_map for the graph to handle arbitrary node numbers.
---> Uses DFS recursively to find all nodes connected to a given starting node.
---> Unvisited nodes are used as entry points to identify new components.
---> Each connected component is stored as a vector and collected into the result.*/
#include <bits/stdc++.h>
using namespace std;
void dfs(int vertex, unordered_map<int, vector<int>>& graph, unordered_set<int>& visited, vector<int>& component) {
    visited.insert(vertex);
    component.push_back(vertex);

    for (int neighbor : graph[vertex]) {
        if (visited.find(neighbor) == visited.end()) {
            dfs(neighbor, graph, visited, component);
        }
    }
}

vector<vector<int>> find_connected_components(unordered_map<int, vector<int>>& graph) {
    unordered_set<int> visited;
    vector<vector<int>> components;

    for (auto& pair : graph) {
        int vertex = pair.first;
        if (visited.find(vertex) == visited.end()) {
            vector<int> component;
            dfs(vertex, graph, visited, component);
            components.push_back(component);
        }
    }

    return components;
}





/*------>Edge Cases to Consider

1. Empty graph
2. Single vertex
3. Disconnected components
4. Self-loops
5. Parallel edges
6. Negative weights
7. Cycles
8. Dense vs sparse graphs
9. Directed vs undirected
10. Bipartite properties



------>Common Pitfalls

1. Not handling disconnected components
2. Incorrect cycle detection
3. Stack overflow in DFS
4. Not considering edge weights
5. Assuming undirected graph
6. Memory issues with adjacency matrix
7. Not handling self-loops



----->Interview Tips

1. Clarify graph properties
2. Choose appropriate representation
3. Consider time/space complexity
4. Handle edge cases explicitly
5. Draw examples
6. Consider optimization opportunities
7. Test with small graphs first
8. Discuss trade-offs



------> Real-World Applications

1. Social Networks: Friend connections
2. Computer Networks: Network topology
3. GPS Navigation: Road networks
4. Recommendation Systems: User-item relationships
5. Compiler Design: Control flow analysis
6. Biology: Protein interaction networks
7. Circuit Design: Electronic circuits
*/