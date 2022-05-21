// Time complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph.
// Space Complexity: O(V), since an extra visited array of size V is required.

// Applications:
// Detecting cycle in a graph/ back edges
// find a path between two given vertices u and z
//  Topological Sorting
//  Finding Strongly Connected Components of a graph
//  Solving puzzles with only one solution, such as mazes


#include<bits/stdc++.h> 
using namespace std; 

void DFSRec(vector<int> adj[], int s, bool visited[]) 
{ 	
    visited[s]=true;
    
    for(int u:adj[s])
    {
        if(visited[u]==false)
            DFSRec(adj,u,visited);
    }
}

int DFS(vector<int> adj[], int V){
    int count=0;
    bool visited[V]; 
	
    for(int i = 0;i<V; i++) 
	visited[i] = false;
		
    for(int i=0;i<V;i++)  //to consider disconnected graphs also, we run this loop
    {
        if(visited[i]==false)
            {DFSRec(adj,i,visited);
	     count++;} //for counting no. of islands
    }
    return count;
}

void addEdge(vector<int> adj[], int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main() 
{ 
	int V=5;
	vector<int> adj[V];
	addEdge(adj,0,1); 
	addEdge(adj,0,2); 
	addEdge(adj,1,2);
	addEdge(adj,3,4);

	cout << "Number of connected components: "<< DFS(adj,V); 

	return 0; 
} 
