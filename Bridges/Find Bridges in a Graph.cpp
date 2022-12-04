//both articulation pts and bridges are for an undirected graph

// An edge in an UNdirected connected graph is a bridge if removing it disconnects the graph. 
// For a disconnected undirected graph, definition is similar, a bridge is an edge removing which increases number of disconnected components. 
// Like Articulation Points, bridges represent vulnerabilities in a connected network and are useful for designing reliable networks


// Naive soln:
// 1) For every edge (u, v), do following 
// …..a) Remove (u, v) from graph(adjacency list/matrix)
// ..…b) See if the graph remains connected (We can either use BFS or DFS) 
// …..c) Add (u, v) back to the graph.
// Time complexity of above method is O(E*(V+E)) for a graph represented using adjacency list. 


// Efficient solution:
// A O(V+E) algorithm to find all Bridges 
// The idea is similar to O(V+E) algorithm for Articulation Points. 
// We do DFS traversal of the given graph. In DFS tree an edge (u, v) (u is parent of v in DFS tree) is bridge 
// if there does not exist any other alternative to reach u or an ancestor of u from subtree rooted with v. 
// As discussed in Articulation points, the value low[v] indicates earliest visited vertex reachable from subtree rooted with v. 
// The condition for an edge (u, v) to be a bridge is, “low[v] > disc[u]”. 



#include<iostream> 
#include <list> 
#define NIL -1 
using namespace std; 

// A class that represents an undirected graph 
class Graph 
{ 
	int V; // No. of vertices 
	list<int> *adj; // A dynamic array of adjacency lists 
	void bridgeUtil(int v, bool visited[], int disc[], int low[], 
					int parent[]); 
public: 
	Graph(int V); // Constructor 
	void addEdge(int v, int w); // to add an edge to graph 
	void bridge(); // prints all bridges 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); 
	adj[w].push_back(v); // Note: the graph is undirected 
} 


void Graph::bridgeUtil(int u, bool visited[], int disc[], int low[], int parent[]) //ALL ARE PASSED BY REFERENCE => just like articulation points
{ 
	static int time = 0; //instead of static int, we could simply do => void bridgeUtil(..., int & time, ...) =>just like articulation points

	visited[u] = true; 

	disc[u] = low[u] = ++time; 
	
	//NO NEED of children variable here (was needed in articulation pts)

	list<int>::iterator i; 
	for (i = adj[u].begin(); i != adj[u].end(); ++i) 
	{ 
		int v = *i; 

		if (!visited[v]) 
		{ 
			parent[v] = u; 
			
			//No children++ here like articulation points
			
			bridgeUtil(v, visited, disc, low, parent); 

			low[u] = min(low[u], low[v]); 

			if (low[v] > disc[u])  //NOT >=
				cout << u <<" " << v << endl; 
		} 

		else if (v != parent[u])      
			low[u] = min(low[u], disc[v]);
	} 
} 

void Graph::bridge() //VVIMP....we have to make 2 functions.....1 se kaam NAHI hoga!!!...VVIMP....FOR BOTH BRIDGE AND ARTICULATION PT.
{ 
	// Mark all the vertices as not visited 
	bool *visited = new bool[V]; 
	int *disc = new int[V]; 
	int *low = new int[V]; 
	int *parent = new int[V]; 

	// Initialize parent and visited arrays 
	for (int i = 0; i < V; i++) 
	{ 
		parent[i] = NIL; 
		visited[i] = false; 
	} 

	// Call the recursive helper function to find Bridges 
	// in DFS tree rooted with vertex 'i' 
	for (int i = 0; i < V; i++) 
		if (visited[i] == false) 
			bridgeUtil(i, visited, disc, low, parent); 
} 


int main() 
{ 
	cout << "Bridges in first graph \n"; 
	Graph g(5); 
	g.addEdge(1, 0); 
	g.addEdge(0, 2); 
	g.addEdge(2, 1); 
	g.addEdge(0, 3); 
	g.addEdge(3, 4); 
	g.bridge(); 

	return 0; 
} 
