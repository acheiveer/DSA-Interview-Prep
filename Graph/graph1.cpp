
/***************** Graph Data Structure and Algorithms ***************
 * 
  ----> A graph is a non-linear data structure consisting of vertices (nodes) and edges that connect these vertices. 
        Graphs are used to represent networks, relationships, and various real-world problems from social networks to computer networks.


------> Important Terminologies

1. Vertex/Node: Basic unit of a graph
2. Edge: Connection between two vertices
3. Directed Graph: Edges have direction
4. Undirected Graph: Edges are bidirectional
5. Weighted Graph: Edges have weights/costs
6. Path: Sequence of vertices connected by edges
7. Cycle: Path that starts and ends at same vertex
8. (DAG): Directed Acyclic Graph (no cycles)
9. Connected Component: Subset of connected vertices
10. Degree: Number of edges connected to a vertex
11. Tree: Connected graph with no cycles
12. Bipartite Graph: Vertices can be split into two sets
13. Strongly Connected: Every vertex reachable from every other
14. Adjacency: Direct connection between vertices



--------> Graph Representations

1. Adjacency Matrix:
    -> 2D array where matrix[i][j] represents edge from i to j
    -> Space: O(V²)
    -> Good for dense graphs

2. Adjacency List:
    ->Array of lists where list[i] contains vertices adjacent to i
    -> Space: O(V + E)
    -> Good for sparse graphs

3. Edge List:
    -> List of all edges in graph
    -> Space: O(E)
    -> Good for algorithms that process all edges



-----> Time Complexity Analysis

Operation	  Adjacency List	Adjacency Matrix
Add Vertex	      O(1)	           O(V²)
Add Edge	      O(1)	           O(1)
Remove Vertex	  O(V + E)	       O(V²)
Remove Edge	      O(E)	           O(1)
Query Edge	      O(V)	           O(1)
Find Neighbors	  O(V)	           O(V)
Storage Space	  O(V + E)	       O(V²)    




---------> LeetCode Questions with pattern
Graph Traversal Patterns (DFS & BFS) 
Pattern 19: Graph DFS - Connected Components / Island Counting                 130. Surrounded Regions, 200. Number of Islands, 417. Pacific Atlantic Water Flow, 547. Number of Provinces, 695. Max Area of Island, 733. Flood Fill, 841. Keys and Rooms, 1020. Number of Enclaves, 1254. Number of Closed Islands, 1905. Count Sub Islands, 2101. Detonate the Maximum Bombs 
Pattern 20: Graph BFS - Connected Components / Island Counting                 127. Word Ladder, 542. 01 Matrix, 994. Rotting Oranges, 1091. Shortest Path in Binary Matrix 
Pattern 21: Graph DFS - Cycle Detection (Directed Graph)                       207. Course Schedule, 210. Course Schedule II, 802. Find Eventual Safe States, 1059. All Paths from Source Lead to Destination 
Pattern 22: Graph BFS - Topological Sort (Kahn's Algorithm)                    207. Course Schedule, 210. Course Schedule II, 269. Alien Dictionary, 310. Minimum Height Trees, 444. Sequence Reconstruction, 1136. Parallel Courses, 1857. Largest Color Value in a Directed Graph, 2050. Parallel Courses III, 2115. Find All Possible Recipes from Given Supplies, 2392. Build a Matrix With Conditions 
Pattern 23: Graph - Deep Copy / Cloning                                        133. Clone Graph 
Pattern 24: Graph - Shortest Path (Dijkstra's Algorithm)                       743. Network Delay Time, 778. Swim in Rising Water, 1514. Path with Maximum Probability, 1631. Path With Minimum Effort, 1976. Number of Ways to Arrive at Destination, 2045. Second Minimum Time to Reach Destination, 2203. Minimum Weighted Subgraph With the Required Paths, 2290. Minimum Obstacle Removal to Reach Corner, 2577. Minimum Time to Visit a Cell In a Grid, 2812. Find the Safest Path in a Grid 
Pattern 25: Graph - Shortest Path (Bellman-Ford / BFS+K)                       787. Cheapest Flights Within K Stops 
Pattern 26: Graph - Union-Find (Disjoint Set Union - DSU)                      200. Number of Islands, 261. Graph Valid Tree, 305. Number of Islands II, 323. Number of Connected Components in an Undirected Graph, 3 547. Number of Provinces, 684. Redundant Connection, 4 721. Accounts Merge, 737. Sentence Similarity II, 947. Most Stones Removed with Same Row or Column, 952. Largest Component Size by Common Factor, 959. Regions Cut By Slashes, 1101. The Earliest Moment When Everyone Bec



*************************** Implementation *****************************/


// 1. Basic Graph using Adjacency List
/******************************************** 
--> Graph Representation: The graph uses an adjacency list, implemented via unordered_map<int, list<int>> for efficient storage and lookup.
--> Directed vs Undirected: The constructor allows flexibility to create either type.
--> Edge Addition: Automatically creates vertices if they are not already present.
--> Duplicate Edge Prevention: getEdges uses a set to avoid counting duplicate edges in undirected graphs */
#include <bits/stdc++.h>
using namespace std;
class Graph {
private:
    unordered_map<int, list<int>> adjList;
    bool directed;

public:
    // Constructor
    Graph(bool isDirected = false) {
        directed = isDirected;
    }

    // Add a vertex to the graph
    void addVertex(int vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = list<int>();
        }
    }

    // Add an edge between two vertices
    void addEdge(int v1, int v2) {
        addVertex(v1);
        addVertex(v2);
        adjList[v1].push_back(v2);
        if (!directed) {
            adjList[v2].push_back(v1);
        }
    }

    // Get all vertices
    vector<int> getVertices() {
        vector<int> vertices;
        for (auto& entry : adjList) {
            vertices.push_back(entry.first);
        }
        return vertices;
    }

    // Get all edges 
    vector<pair<int, int>> getEdges() {
        vector<pair<int, int>> edges;
        set<pair<int, int>> seen; // to avoid duplicates in undirected graph
        
        for (auto& entry : adjList) {
            int vertex = entry.first;
            list<int>& neighbors = entry.second;
            
            for (int neighbor : neighbors) {
                if (!directed) {
                    // avoid duplicate edges like (1,2) and (2,1)
                    if (seen.find({neighbor, vertex}) == seen.end()) {
                        edges.emplace_back(vertex, neighbor);
                        seen.insert({vertex, neighbor});
                    }
                } else {
                    edges.emplace_back(vertex, neighbor);
                }
            }
        }
        return edges;
    }

    // Print the graph 
    void printGraph() {
        for (auto& entry : adjList) {
            int vertex = entry.first;
            list<int>& neighbors = entry.second;
            
            cout << vertex << ": ";
            for (int neighbor : neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};




// 2. Weighted Graph Implementation
/******************************************** 
--> Data Structure:
     -> unordered_map<int, vector<pair<int, int>>> is used to store the graph.
        -> Each vertex maps to a list of (neighbor, weight) pairs.
--> Directed vs Undirected:
     -> If the graph is undirected, edges are bidirectionally added with the same weight.
--> Edge Weight: Weights can represent costs, distances, or capacities depending on the problem.
 */
#include <bits/stdc++.h>
using namespace std;

class WeightedGraph {
private:
    unordered_map<int, vector<pair<int, int>>> adjList; // vertex -> list of (neighbor, weight)
    bool directed;

public:
    // Constructor
    WeightedGraph(bool isDirected = false) {
        directed = isDirected;
    }

    // Add a vertex
    void addVertex(int vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = vector<pair<int, int>>();
        }
    }

    // Add a weighted edge
    void addEdge(int v1, int v2, int weight) {
        addVertex(v1);
        addVertex(v2);
        adjList[v1].push_back({v2, weight});
        if (!directed) {
            adjList[v2].push_back({v1, weight});
        }
    }

    // Get all vertices
    vector<int> getVertices() {
        vector<int> vertices;
        for (auto& entry : adjList) {
            vertices.push_back(entry.first);
        }
        return vertices;
    }

    // Get all weighted edges
    vector<pair<pair<int, int>, int>> getEdges() {
        vector<pair<pair<int, int>, int>> edges; // ((v1, v2), weight)
        set<pair<int, int>> seen; // to avoid duplicates in undirected graph
        
        for (auto& entry : adjList) {
            int vertex = entry.first;
            vector<pair<int, int>>& neighbors = entry.second;
            
            for (auto& neighborPair : neighbors) {
                int neighbor = neighborPair.first;
                int weight = neighborPair.second;
                
                if (!directed) {
                    // avoid duplicate edges like (1,2) and (2,1)
                    if (seen.find({neighbor, vertex}) == seen.end()) {
                        edges.push_back({{vertex, neighbor}, weight});
                        seen.insert({vertex, neighbor});
                    }
                } else {
                    edges.push_back({{vertex, neighbor}, weight});
                }
            }
        }
        return edges;
    }

    // Print the graph - 
    void printGraph() {
        for (auto& entry : adjList) {
            int vertex = entry.first;
            vector<pair<int, int>>& neighbors = entry.second;
            
            cout << vertex << ": ";
            for (auto& neighborPair : neighbors) {
                int neighbor = neighborPair.first;
                int weight = neighborPair.second;
                cout << "(" << neighbor << ", " << weight << ") ";
            }
            cout << endl;
        }
    }

    // Get neighbors of a vertex with their weights
    vector<pair<int, int>> getNeighbors(int vertex) {
        if (adjList.find(vertex) != adjList.end()) {
            return adjList[vertex];
        }
        return vector<pair<int, int>>();
    }

    // Check if an edge exists
    bool hasEdge(int v1, int v2) {
        if (adjList.find(v1) == adjList.end()) return false;
        
        for (auto& neighborPair : adjList[v1]) {
            if (neighborPair.first == v2) {
                return true;
            }
        }
        return false;
    }

    // Get weight of an edge (returns -1 if edge doesn't exist)
    int getWeight(int v1, int v2) {
        if (adjList.find(v1) == adjList.end()) return -1;
        
        for (auto& neighborPair : adjList[v1]) {
            if (neighborPair.first == v2) {
                return neighborPair.second;
            }
        }
        return -1;
    }
};