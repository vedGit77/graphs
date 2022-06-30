#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
	int src, dest;
};

class Graph
{
	public:
		// V-> Number of vertices, E-> Number of edges
		int V, E;

		// graph is represented as an array of edges
		Edge* edge;
};

Graph* createGraph(int V, int E)
{
	Graph* graph = new Graph();
	graph->V = V;
	graph->E = E;

	graph->edge = new Edge[graph->E * sizeof(Edge)];

	return graph;
}

// A utility function to find the subset of an element i
int find(int parent[], int b)
{
	if (parent[b] == -1)  
		return b; //basically a new set formed with only 1 element inside it (that element is b)
	return find(parent, parent[b]);
}

// A utility function to do union of two subsets
void Union(int parent[], int x, int y)
{
	parent[x] = y;
}


int isCycle(Graph* graph)
{
	// Allocate memory for creating V subsets
	int* parent = new int[graph->V * sizeof(int)];

	memset(parent, -1, sizeof(int) * graph->V); // -1 initialization..... -1 means its representative of its own set

	for (int i = 0; i < graph->E; ++i) // Iterate through all edges of graph
  	{
		int x = find(parent, graph->edge[i].src);
		int y = find(parent, graph->edge[i].dest);

		if (x == y)
			return 1;  
    
		Union(parent, x, y);
	}
	return 0;
}


int main()
{
	/* Let us create the following graph
		0
		| \
		| \
		1---2 */
	int V = 3, E = 3;
	Graph* graph = createGraph(V, E);

	// add edge 0-1
	graph->edge[0].src = 0;
	graph->edge[0].dest = 1;

	// add edge 1-2
	graph->edge[1].src = 1;
	graph->edge[1].dest = 2;

	// add edge 0-2
	graph->edge[2].src = 0;
	graph->edge[2].dest = 2;

	if (isCycle(graph))
		cout << "graph contains cycle";
	else
		cout << "graph doesn't contain cycle";

	return 0;
}
