// intro:
// A vertex in an UNdirected connected graph is an articulation point (or cut vertex) if removing it (and edges through it) disconnects the graph. 
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








//code is very similar to bridges in a graph...just 2 things extra...children array, and the 2 cases(if not yet visited)
//in both places low[u]=min().....u is parent	

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

void Graph::APUtil(int u, bool visited[], int disc[], int low[], int parent[], bool ap[]) //ALL PASSED BY REFERENCE => since all are arrays
{ 
	 
	static int time = 0;  //static int hai...instead of this, we could also do=> APUtil(..., int & time, ...) =>same thing

	int children = 0; 

	visited[u] = true; 

	disc[u] = low[u] = ++time; //initially wehn we do DFS, we assign discovery time and low time equal //after the DFS recursion ends, low time reduces

	list<int>::iterator i; 
	for (i = adj[u].begin(); i != adj[u].end(); ++i) 
	{ 
		int v = *i;

		if (!visited[v]) //descendants of a node are NOT visited
		{ 
			children++; 
			parent[v] = u; 
			APUtil(v, visited, disc, low, parent, ap); //IMP: recursion=> then only we will get children, parent, low and disc time (initially we will set low and disc equal) for each node

			low[u] = min(low[u], low[v]); //min(low[u],low[v]) is logical....immidiate descendant checking with parent


			if (parent[u] == NIL && children > 1)  //if more than 1 child (AND root Node...NO other parent), then surely an articulation point
				ap[u] = true; 
			if (parent[u] != NIL && low[v] >= disc[u])//if (NON parent root) && (NO back edge)......ek bhi NON back edge mil jaye, then true
				ap[u] = true;  //think...if we get back edges from descendant to ancestor, then the parent WON'T be an articulation point
		}                              //because then the subgraphs would be connected even if we remove the parent
						//thus we need ATLEAST 1 NON back edge to prove articulation point (parent MUST be non root)
		
		else if (v != parent[u])    //keep updating the low[] array values if already visited that node (and that node is NOT parent)
			low[u] = min(low[u], disc[v]); //NOT min(low[u],low[v])...REASON: graph is directed...u points to v....so if v is already visited, then we will compare its disc time, NOT low time
							// see the defn of low[] again...or see the photo attached
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
	
	for (int i = 0; i < V; i++)   //do with loop....to consider disconnected graphs too
		if (visited[i] == false) 
			APUtil(i, visited, disc, low, parent, ap); 

	for (int i = 0; i < V; i++) //to consider multiple articulation points
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
