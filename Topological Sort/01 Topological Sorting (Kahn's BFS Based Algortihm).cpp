//Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge u->v 
// vertex u comes before v in the ordering.

// Note: WORKS ONLY FOR DAG (DIRECTED ACYCLIC GRAPH)!
// Note: Topo sorting of a graph may NOT be unique.

//then how did we use it for cycle detection in directed graph??....we modified it using count variable!

// The time complexity of topological sort using Kahn’s algorithm is O(V+E), where V = Vertices, E = Edges.
// Space complexity = O(V)

#include<bits/stdc++.h> 
using namespace std; 

void topologicalSort(vector<int> adj[], int V) 
{ 
    vector<int> in_degree(V, 0); 
  
    for (int u = 0; u < V; u++) 
    { 
        for (int x:adj[u]) 
            in_degree[x]++; 
    } 
  
    queue<int> q; 
    for (int i = 0; i < V; i++) 
        if (in_degree[i] == 0) 
            q.push(i); 

  
    while (!q.empty()) 
    { 
        int u = q.front(); 
        q.pop(); 
        cout<<u<<" ";   //VVIMP => this 'u' will be the order of topo sort => neeche for loop mei cout NAHI karna
  
        for (int x: adj[u]) 
        {
            in_degree[x]--;
            if (in_degree[x] == 0) 
                q.push(x); 
        }
    } 
}

void addEdge(vector<int> adj[], int u, int v){
    adj[u].push_back(v);
}

int main() 
{ 
    int V=5;
    vector<int> adj[V];
    addEdge(adj,0, 2); 
    addEdge(adj,0, 3); 
    addEdge(adj,1, 3); 
    addEdge(adj,1, 4); 
    addEdge(adj,2, 3);  
  
    cout << "Following is a Topological Sort of\n"; 
    topologicalSort(adj,V);

    return 0; 
} 
