//VVIMP NOTE: Khans Algo works ONLY for ACYCLIC GRAPHS (in Topological Sort)!
//then how did we use it for cycle detection in directed graph??....we modified it using count variavle!


//We can NOT use the same method as cycle detection in undirected graph
// eg  1 -> 2 -> 3 <- - 
//     |              |
//     - - -> 4 - - - -
// NOT a cycle....but the undirected graph cycle detection code will say that theres a cycle

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
        if (in_degree[i] == 0) //IMP...initially push ones having in_degree 0
            q.push(i); 

    int count=0;  //exact same as topological/khans algo...just this count variable is extra
    while (!q.empty()) 
    { 
        int u = q.front(); 
        q.pop(); 
  
        for (int x: adj[u]) 
	{
		in_degree[x]--;
		if (in_degree[x] == 0) 
                    q.push(x); 
	}
        count++;  //counting the number of vertices popped 
    } 
	
    if (count != V) {//whenever theres a cycle, surely (count < V), because the vertices of the cycle will always have (indegree > 0)
        cout << "There exists a cycle in the graph\n"; 
    }
    else{
        cout << "There exists no cycle in the graph\n";
    }
}

void addEdge(vector<int> adj[], int u, int v){
    adj[u].push_back(v);
}

int main() 
{ 
    int V=5;
    vector<int> adj[V];
    addEdge(adj,0, 1); 
    addEdge(adj,4, 1); 
    addEdge(adj,1, 2); 
    addEdge(adj,2, 3); 
    addEdge(adj,3, 1);  
  
    topologicalSort(adj,V);

	return 0; 
} 
