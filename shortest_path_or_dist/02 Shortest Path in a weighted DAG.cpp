//DAG- directed acyclic graph
//graph is weightes
//aim is to print shortest dist from source vertex to every other vertex

//Following is complete algorithm for finding shortest distances. 
// 1) Initialize dist[] = {INF, INF, ….} and dist[s] = 0 where s is the source vertex. 
// 2) Create a topological order of all vertices(without considering the weights)
// 3) Do following for every vertex u in topological order. 
// ………..Do following for every adjacent vertex v of u 
// ………………if (dist[v] > dist[u] + weight(u, v)) 
// ………………………dist[v] = dist[u] + weight(u, v) 

#include <bits/stdc++.h> 
#define INF INT_MAX 
using namespace std; 

class AdjListNode 
{ 
	int v; 
	int weight; 
public: 
	AdjListNode(int _v, int _w) { v = _v; weight = _w;} 
	int getV()	 { return v; } 
	int getWeight() { return weight; } 
}; 

class Graph 
{ 
	int V;

	list<AdjListNode> *adj; 

	void topologicalSortUtil(int v, bool visited[], stack<int> &Stack); 
public: 
	Graph(int V); 
 
	void addEdge(int u, int v, int weight); 
 
	void shortestPath(int s); 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<AdjListNode>[V]; 
} 

void Graph::addEdge(int u, int v, int weight) 
{ 
	AdjListNode node(v, weight); 
	adj[u].push_back(node);  
} 

void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack) //topological sort using DFS approach
{ 
	visited[v] = true; 

	list<AdjListNode>::iterator i; 
	for (i = adj[v].begin(); i != adj[v].end(); ++i) 
	{ 
		AdjListNode node = *i; 
		if (!visited[node.getV()]) 
			topologicalSortUtil(node.getV(), visited, Stack); 
	} 

	Stack.push(v); 
} 

void Graph::shortestPath(int s) 
{ 
	stack<int> Stack; //stack for topological sort
	int dist[V]; 

	bool *visited = new bool[V]; //visited is a boolean array of size V
	for (int i = 0; i < V; i++) 
		visited[i] = false; 
 
	for (int i = 0; i < V; i++) //loop to consider full graph for topological sort
		if (visited[i] == false) 
			topologicalSortUtil(i, visited, Stack); //store the topological sort in the stack

	for (int i = 0; i < V; i++) 
		dist[i] = INF; //initial dist =  infinity / INT_MAX
	dist[s] = 0; //for the source element...distance from itself

	while (Stack.empty() == false) 
	{  
		int u = Stack.top(); 
		Stack.pop(); 
 
		list<AdjListNode>::iterator i; 
		if (dist[u] != INF) 
		{ 
			for (i = adj[u].begin(); i != adj[u].end(); ++i) 
				if ( dist[i->getV()] > dist[u] + i->getWeight() ) //relax function
					dist[i->getV()] = dist[u] + i->getWeight(); 
		} 
	} 

	for (int i = 0; i < V; i++) 
		(dist[i] == INF)? cout << "INF ": cout << dist[i] << " "; 
} 

int main() 
{ 
	Graph g(6); 
	g.addEdge(0, 1, 2); 
	g.addEdge(0, 4, 1); 
	g.addEdge(1, 2, 3); 
	g.addEdge(4, 2, 2); 
	g.addEdge(4, 5, 4); 
	g.addEdge(2, 3, 6); 
	g.addEdge(5, 3, 1);

	int s = 0; 
	cout << "Following are shortest distances from source " << s <<" \n"; 
	g.shortestPath(s); 

	return 0; 
} 
