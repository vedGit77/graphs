// graph where every edge has weight as either 0 or 1. 
// A source vertex is also given in the graph. 
// Find the shortest path from source vertex to every other vertex. 


// In this we will NOT use bool array to mark visited nodes (like we did in normal BFS)
// but at each step we will check for the optimal distance condition. 
  
// We use DEQUEUE to store the node. 
// if a edge having weight = 0 => node is pushed at front of DEQUEUE, and if a edge having weight = 1 => pushed at back of DEQUEUE.
// so that vertices are processed in increasing order of weights.
  
// The approach is similar to Dijkstra => if the shortest distance to node is relaxed by the previous node => then only it will be pushed in the queue. 

// The above idea works in all cases.
// when we pop a vertex (like Dijkstra), it is the minimum weight vertex among remaining vertices. 
// If there is a 0 weight vertex adjacent to it, then this adjacent has same distance. 
// If there is a 1 weight adjacent, then this adjacent has maximum distance among all vertices in dequeue (because all other vertices are either adjacent of currently popped vertex or adjacent of previously popped vertices).




/* no.of vertices */
#define V 9

// a structure to represent edges
struct node
{
	// two variable one denote the node and other the weight
	int to, weight;
};

// vector to store edges
vector <node> edges[V];


void zeroOneBFS(int src)
{
	// Initialize distances from given source
	int dist[V];
	for (int i=0; i<V; i++)
		dist[i] = INT_MAX;

	// double ende queue to do BFS.
	deque <int> Q;
	dist[src] = 0;
	Q.push_back(src);

	while (!Q.empty())
	{
		int v = Q.front();
		Q.pop_front();

		for (int i=0; i<edges[v].size(); i++)
		{
			// checking for the optimal distance
			if (dist[edges[v][i].to] > dist[v] + edges[v][i].weight)
			{
				dist[edges[v][i].to] = dist[v] + edges[v][i].weight;

				if (edges[v][i].weight == 0)
					Q.push_front(edges[v][i].to);  //push_front
				else
					Q.push_back(edges[v][i].to);   //push_back
			}
		}
	}

	for (int i=0; i<V; i++) // printing the shortest distances
		cout << dist[i] << " ";
}
