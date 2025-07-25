#include <bits/stdc++.h>
#define LIM 3000
using namespace std;

vector<int> adj[LIM];
bool visited[LIM];

void addEdge(int u, int v) 
{ 
    adj[u].push_back(v);
    adj[v].push_back(u);  // Because this is an undirected graph
} 

void dfs_iterative(int src)
{
    stack<int> stck;
    stck.push(src);

    while(!stck.empty())
    {
        int u = stck.top();
        stck.pop();

        if (visited[u]) continue;
        
        visited[u] = true;
        cout << u << " ";

        for(auto v : adj[u])
        {
            if(!visited[v])
                stck.push(v);
        }
    }
}

void dfs_recursive(int u)
{
    visited[u] = true;
    cout << u << " ";

    for(int v : adj[u])
    {
        if(!visited[v])
            dfs_recursive(v);
    }
}

int main()
{
    int V, E, u, v, src;

    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    for(int i = 0; i < E; i++)
    {
        cout << i+1 << ". Enter vertex u and v: ";
        cin >> u >> v;
        addEdge(u, v);
    }

    cout << "Enter source node for iterative DFS: ";
    cin >> src;
    memset(visited, 0, sizeof(visited));
    cout << "Iterative DFS => ";
    dfs_iterative(src);
    cout << endl;

    cout << "Enter source node for recursive DFS: ";
    cin >> src;
    memset(visited, 0, sizeof(visited));
    cout << "Recursive DFS => ";
    dfs_recursive(src);
    cout << endl;

    return 0;
}
