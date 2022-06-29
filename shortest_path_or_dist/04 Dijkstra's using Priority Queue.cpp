//A few things to take care of:
// 1. No visited array!!!!because here we may traverse the same element multiple times (dont worry, we push new item only when if statement is true)
// 2. use MIN heap
// 3. min heap should be of a PAIR (distance,vectex)...since then the top element will be according to the SMALLEST distance
// 4. here the adj should be of the form vector<vector<pair<int,int>>>adj.....basically vector of vector of a pair


#include<bits/stdc++.h>
using namespace std;

# define INF 0x3f3f3f3f
// iPair ==> Integer Pair
typedef pair<int, int> iPair;


class Graph
{
	int V; // No. of vertices

	// In a weighted graph, we need to store vertex and weight pair for every edge
	list< pair<int, int> > *adj;

public:
	Graph(int V); // Constructor

	// function to add an edge to graph
	void addEdge(int u, int v, int w);

	// prints shortest path from s
	void shortestPath(int s);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<iPair> [V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

// Prints shortest paths from src to all other vertices
void Graph::shortestPath(int src)
{
	// we use MIN heap, not max heap...because we want min distance...so topmost element gives the min distance...
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;//NOTE: priority_queue mei if we want MIN heap, ALWAYS THIS WIERD SYNTAX....vector<iPair> in the middle

	vector<int> dist(V, INF);

	// Insert source itself in priority queue and initialize its distance as 0.
	pq.push(make_pair(0, src));
	dist[src] = 0;

	while (!pq.empty())
	{
		int u = pq.top().second;//pq.top().first always stores the minimum distance of vertex x from the source vertex, and pq.top().second stores the vertex no. x
		pq.pop();

		// 'i' is used to get all adjacent vertices of a vertex
		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)  //OR for(auto i :adj[u])...simpler syntax
		{
			// Get vertex label and weight of current adjacent of u.
			int v = (*i).first;
			int weight = (*i).second;

			// If there is shorted path to v through u.
			if (dist[v] > dist[u] + weight)
			{
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v)); //OR pq.push({dist[v], v})...simpler syntax
			}
		}
	}

	printf("Vertex Distance from Source\n");
	for (int i = 0; i < V; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
}

int main()
{
	// create the graph given in above figure
	int V = 9;
	Graph g(V);

	// making above shown graph
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	g.shortestPath(0);

	return 0;
}
	
