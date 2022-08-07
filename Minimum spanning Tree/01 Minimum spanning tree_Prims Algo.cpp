//DONT USE PRIMS!
// Prims Algo-> O(v^2) ->sometimes gives TLE


//THUS USE KRUSKAL ALWAYS


// What is Minimum Spanning Tree? 
// Given a connected and undirected graph, a spanning tree of that graph is a subgraph that is a tree and connects all the vertices together. 
// A single graph can have many different spanning trees. A minimum spanning tree (MST) or minimum weight spanning tree for a 
// weighted, connected, undirected graph is a spanning tree with a weight less than or equal to the weight of every other spanning tree. 
// The weight of a spanning tree is the sum of weights given to each edge of the spanning tree.

// How many edges does a minimum spanning tree has? 
// A minimum spanning tree has (V – 1) edges where V is the number of vertices in the given graph. 

// Algorithm 
// 1) Create a set mstSet that keeps track of vertices already included in MST. 
// 2) Assign a key value to all vertices in the input graph. Initialize all key values as INFINITE. 
// 	Assign key value as 0 for the first vertex so that it is picked first. 
// 3) While mstSet doesn’t include all vertices 
// ….a) Pick a vertex u which is not there in mstSet and has minimum key value. 
// ….b) Include u to mstSet. 
// ….c) Update key value of all adjacent vertices of u. To update the key values, iterate through all adjacent vertices. 
// 	For every adjacent vertex v, if weight of edge u-v is less than the previous key value of v, update the key value as weight of u-v

#include <bits/stdc++.h> 
using namespace std; 
#define V 4

int primMST(int graph[V][V]) 
{ 

	int res=0; 
	bool mstSet[V]; 
	int key[V];
	fill(key,key+V,INT_MAX);
	key[0]=0;

	for (int count = 0; count < V ; count++) //outer loop
	{ 
		int u = -1; //after processing a vertex, u =-1 ...always initialized this way

		for(int i=0;i<V;i++)  
		    if(!mstSet[i] && (u==-1||key[i]<key[u])) 
		        u=i;   //step 3a.//Pick a vertex u which is NOT there in mstSet and has MINIMUM key value. 
		
		mstSet[u] = true; //step 3b.//Include u to mstSet. 
		res+=key[u];

		for (int v = 0; v < V; v++) //step 3c.//Update key value of all adjacent vertices of u.
			if (graph[u][v]!=0 && mstSet[v] == false) 
				key[v] = min(key[v],graph[u][v]); //learn as: since unvisited nodes ka key[] was infinite,thus take min(key[v],graph[u][v])
							 //in Dijsktras, it was min(dist[v],dist[u]+graph[u][v]) since there we had to find shortest distance
	} 		
    return res;
} 

int main() 
{ 
	int graph[V][V] = { { 0, 5, 8, 0}, 
			    { 5, 0, 10, 15 }, 
			    { 8, 10, 0, 20 }, 
			    { 0, 15, 20, 0 },}; 

	cout<<primMST(graph); 

	return 0; 
} 
