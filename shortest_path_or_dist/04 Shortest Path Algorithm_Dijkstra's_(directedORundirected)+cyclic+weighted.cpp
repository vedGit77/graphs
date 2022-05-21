// Dijkstra's DOES NOT WORK for -ive path weights.

// Given a graph and a source vertex in the graph, find the shortest paths from the source to all vertices in the given graph.

//very similar to prims, but there we had to find minimum spanning tree

// Its NOT the same file as 02 (since it was for DAG)

//  The time complexity for the matrix representation is O(V^2). In this post, O(ELogV) algorithm for adjacency list

// Algorithm:
// 1) Create a set sptSet (shortest path tree set) that keeps track of vertices included in the shortest-path tree, i.e., 
//    whose minimum distance from the source is calculated and finalized. Initially, this set is empty. 
// 2) Assign a distance value to all vertices in the input graph. Initialize all distance values as INFINITE. 
//    Assign distance value as 0 for the source vertex so that it is picked first. 
// 3) While sptSet doesn’t include all vertices 
// ….a) Pick a vertex u which is not there in sptSet and has a minimum distance value. 
// ….b) Include u to sptSet. 
// ….c) Update distance value of all adjacent vertices of u. To update the distance values, iterate through all adjacent vertices. 
//      For every adjacent vertex v, if the sum of distance value of u (from source) and weight of edge u-v, is less than the distance value of v, 
//      then update the distance value of v. 


#include <bits/stdc++.h> 
using namespace std; 
#define V 4

vector<int> djikstra(int graph[V][V],int src) 
{ 

	vector<int> dist(V,INT_MAX);
	dist[src]=0;
	vector<bool> fin(V,false);

	for (int count = 0; count < V-1 ; count++)   //exact same as prims algo
	{ 					     //just that here we need to print the distance array
		int u = -1; 			     //and there we used to print the sum of the array elements

		for(int i=0;i<V;i++)
		    if(!fin[i]&&(u==-1||dist[i]<dist[u]))
		        u=i;
		
		fin[u] = true; 
		
		for (int v = 0; v < V; v++) 
			if (graph[u][v]!=0 && fin[v] == false) 
				dist[v] = min(dist[v],dist[u]+graph[u][v]); 
	} 
    return dist;
} 

int main() 
{ 
	int graph[V][V] = { { 0, 50, 100, 0}, 
			    { 50, 0, 30, 200 }, 
     			    { 100, 30, 0, 20 }, 
			    { 0, 200, 20, 0 },}; 

	for(int x: djikstra(graph,0)){
	    cout<<x<<" ";
	} 

	return 0; 
} 
