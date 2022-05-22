// Kosaraju requires 2 traversals of an undirected graph
// Tarjans algo requires only 1

// Strongly Connected Component relates to directed graph only, but Disc and Low values relate to both directed and undirected graph

// A directed graph is strongly connected if there is a path between all pairs of vertices. 
// A strongly connected component (SCC) of a directed graph is a maximal strongly connected subgraph.

// Tarjan Algorithm is based on following facts: 
// 1. DFS search produces a DFS tree/forest 
// 2. Strongly Connected Components form subtrees of the DFS tree. 
// 3. If we can find the head of such subtrees, we can print/store all the nodes in that subtree (including head) and that will be one SCC. 
// 4. There is no back edge from one SCC to another (There can be cross edges, but cross edges will not be used while processing the graph).

// To find head of a SCC, we calculate disc and low array (as done for articulation point, bridge, biconnected component). 
// As discussed in the previous posts, low[u] indicates earliest visited vertex (the vertex with minimum discovery time) that can be reached from 
// subtree rooted with u. A node u is head if disc[u] = low[u].

// To track the subtree rooted at head, we can use a stack (keep pushing node while visiting). 
// When a head node found, pop all nodes from stack till you get head out of stack.

// To make sure, we don’t consider cross edges, when we reach a node which is already visited, 
// we should process the visited node only if it is present in stack, else ignore the node.  


#include<iostream> 
#include <list> 
#include <stack> 
#define NIL -1 
using namespace std; 


class Graph 
{ 
	int V; 
	list<int> *adj; 

	void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]); 
public: 
	Graph(int V); 
	void addEdge(int v, int w); 
	void SCC(); 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); 
} 


void Graph::SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]) 
{ 
	static int time = 0; 

	disc[u] = low[u] = ++time; 
	st->push(u); 
	stackMember[u] = true; 
 
	list<int>::iterator i; 
	for (i = adj[u].begin(); i != adj[u].end(); ++i) 
	{ 
		int v = *i;

		if (disc[v] == -1) 
		{ 
			SCCUtil(v, disc, low, st, stackMember); 

			low[u] = min(low[u], low[v]); 
		} 

		else if (stackMember[v] == true) 
			low[u] = min(low[u], disc[v]); 
	} 

	int w = 0;
	if (low[u] == disc[u]) 
	{ 
		while (st->top() != u) 
		{ 
			w = (int) st->top(); 
			cout << w << " "; 
			stackMember[w] = false; 
			st->pop(); 
		} 
		w = (int) st->top(); 
		cout << w << "\n"; 
		stackMember[w] = false; 
		st->pop(); 
	} 
} 

void Graph::SCC() 
{ 
	int *disc = new int[V]; 
	int *low = new int[V]; 
	bool *stackMember = new bool[V]; 
	stack<int> *st = new stack<int>(); 

	for (int i = 0; i < V; i++) 
	{ 
		disc[i] = NIL; 
		low[i] = NIL; 
		stackMember[i] = false; 
	} 

	for (int i = 0; i < V; i++) 
		if (disc[i] == NIL) 
			SCCUtil(i, disc, low, st, stackMember); 
} 

int main() 
{ 
	cout << "SCCs in the graph \n"; 
	Graph g(5); 
	g.addEdge(1, 0); 
	g.addEdge(0, 2); 
	g.addEdge(2, 1); 
	g.addEdge(0, 3); 
	g.addEdge(3, 4); 
	g.SCC(); 

	return 0; 
} 
