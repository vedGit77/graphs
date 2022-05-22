// intro:
// A vertex in an undirected connected graph is an articulation point (or cut vertex) if removing it (and edges through it) disconnects the graph. 
// Articulation points represent vulnerabilities in a connected network – single points whose failure would split the network into 2 or more components. 
// They are useful for designing reliable networks. 
// For a disconnected undirected graph, an articulation point is a vertex removing which increases number of connected components.


// Naive soln:
// 1) For every vertex v, do following 
// …..a) Remove v from graph (from adjacency list/matrix)
// ..…b) See if the graph remains connected (We can either use BFS or DFS) 
// …..c) Add v back to the graph
// Time complexity of above method is O(V*(V+E)) for a graph




// Efficient soln: (Time complexity is same as DFS which is O(V+E) for adjacency list representation of graph)

// The idea is to use DFS (Depth First Search). In DFS, we follow vertices in tree form called DFS tree. 
// In DFS tree, a vertex u is parent of another vertex v, if v is discovered by u (obviously v is an adjacent of u in graph).
// In DFS tree, a vertex u is articulation point if one of the following two conditions is true. 
// 1) u is root of DFS tree and it has at least two children. 
// 2) u is not root of DFS tree and it has a child v such that NO vertex in subtree 
//    rooted with v has a back edge to one of the ancestors (in DFS tree) of u.
//------------------------------------------Explaining the efficient Approach--------------------------------------------

// We do DFS traversal of given graph with additional code to find out Articulation Points (APs). 
// In DFS traversal, we maintain a parent[] array where parent[u] stores parent of vertex u. 
// Among the above mentioned two cases, the first case is simple to detect. 
// For every vertex, count children. If currently visited vertex u is root (parent[u] is NIL) and has more than two children, print it. 

// How to handle second case? The second case is trickier. We maintain an array disc[] to store discovery time of vertices. 
// For every node u, we need to find out the earliest visited vertex (the vertex with minimum discovery time) that can be reached from subtree rooted with u. 
// So we maintain an additional array low[] which is defined as follows:
// 	low[u] = min(disc[u], disc[w]) 
// where w is an ancestor of u and there is a back edge from some descendant of u to w.
	

#include<iostream> 
#include <list> 
#define NIL -1
using namespace std; 

class Graph 
{ 
	int V; 
	list<int> *adj; 
	void APUtil(int v, bool visited[], int disc[], int low[], int parent[], bool ap[]); 
public: 
	Graph(int V);  
	void addEdge(int v, int w); 
	void AP(); 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); 
	adj[w].push_back(v); 
} 

void Graph::APUtil(int u, bool visited[], int disc[], int low[], int parent[], bool ap[]) 
{ 
	 
	static int time = 0;  //static int hai...thus increments every time

	int children = 0; 

	visited[u] = true; 

	disc[u] = low[u] = ++time; //initially wehn we do DFS, we assign discovery time and low time equal //after the DFS recursion ends, low time reduces

	list<int>::iterator i; 
	for (i = adj[u].begin(); i != adj[u].end(); ++i) 
	{ 
		int v = *i;

		if (!visited[v]) 
		{ 
			children++; 
			parent[v] = u; 
			APUtil(v, visited, disc, low, parent, ap); 

			low[u] = min(low[u], low[v]); 


			if (parent[u] == NIL && children > 1) 
			ap[u] = true; 
			if (parent[u] != NIL && low[v] >= disc[u]) 
			ap[u] = true; 
		} 

		else if (v != parent[u]) 
			low[u] = min(low[u], disc[v]); 
	} 
} 

void Graph::AP() 
{ 
	bool *visited = new bool[V]; 
	int *disc = new int[V]; 
	int *low = new int[V]; 
	int *parent = new int[V]; 
	bool *ap = new bool[V]; 
	
	for (int i = 0; i < V; i++) 
	{ 
		parent[i] = NIL; 
		visited[i] = false; 
		ap[i] = false; 
	} 
	
	for (int i = 0; i < V; i++) 
		if (visited[i] == false) 
			APUtil(i, visited, disc, low, parent, ap); 

	for (int i = 0; i < V; i++) 
		if (ap[i] == true) 
			cout << i << " "; 
} 

int main() 
{  
	cout << "Articulation points in first graph \n";
	Graph g(5); 
	g.addEdge(1, 0); 
	g.addEdge(0, 2); 
	g.addEdge(2, 1); 
	g.addEdge(0, 3); 
	g.addEdge(3, 4); 
	g.AP(); 
	
	return 0; 
} 
