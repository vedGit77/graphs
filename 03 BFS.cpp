// Time Complexity: O(V+E), where V is the number of nodes and E is the number of edges.
// Auxiliary Space: O(V)...for the queue and visited array

// Applications:
// Shortest Path 
// Minimum Spanning Tree for unweighted graph (Prims Algo)
// Cycle detection in undirected graph
// Ford–Fulkerson algorithm 



#include<bits/stdc++.h> 
using namespace std; 

void BFS(vector<int> adj[], int s, bool visited[]) 
{ 	
  queue<int>  q;  //BFS uses queue
	
	visited[s] = true; 
	q.push(s); 

	while(q.empty()==false) 
	{ 
      int u = q.front(); 
      q.pop();

      for(int v:adj[u])
      {
          if(visited[v]==false)
          {
              visited[v]=true;
              q.push(v);
          }
      } 
	 } 
}

int BFSDin(vector<int> adj[], int V)
{
    bool visited[V]; 
    int count=0;
  
	  for(int i = 0;i<V; i++) 
		    visited[i] = false;
		
    for(int i=0;i<V;i++)  //we are calling BFS for all V vertices, to consider the disconnected graphs too!
    {
        if(visited[i]==false)
        {
          BFS(adj,i,visited);
          count++; //this counts the no. of islands
        }
    }

    return count;
}

void addEdge(vector<int> adj[], int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main() 
{ 
	int V=7;
	vector<int> adj[V];
	addEdge(adj,0,1); 
	addEdge(adj,0,2); 
	addEdge(adj,2,3); 
	addEdge(adj,1,3); 
	addEdge(adj,4,5);
	addEdge(adj,5,6);
	addEdge(adj,4,6);

	cout << "Number of islands: "<<BFSDin(adj,V); 

	return 0; 
} 
