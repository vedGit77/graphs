// graph where every edge has weight as either 0 or 1. 
// A source vertex is also given in the graph. 
// Find the shortest path from source vertex to every other vertex. 


// In this we will NOT use bool array to mark visited nodes (like we did in normal BFS)
// but at each step we will check for the optimal distance condition. 
  
// We use DEQUEUE to store the node. 
// if a edge having weight = 0 => node is pushed at front of DEQUEUE, and if a edge having weight = 1 => pushed at back of DEQUEUE.
  
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

// Prints shortest distance from given source to every other verte
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

        // Put 0 weight edges to front and 1 weight
        // edges to back so that vertices are processed
        // in increasing order of weights.
        if (edges[v][i].weight == 0)
          Q.push_front(edges[v][i].to);
        else
          Q.push_back(edges[v][i].to);
      }
    }
  }

  for (int i=0; i<V; i++) // printing the shortest distances
    cout << dist[i] << " ";
}

void addEdge(int u, int v, int wt)
{
edges[u].push_back({v, wt});
edges[v].push_back({u, wt});
}

// Driver function
int main()
{
	addEdge(0, 1, 0);
	addEdge(0, 7, 1);
	addEdge(1, 7, 1);
	addEdge(1, 2, 1);
	addEdge(2, 3, 0);
	addEdge(2, 5, 0);
	addEdge(2, 8, 1);
	addEdge(3, 4, 1);
	addEdge(3, 5, 1);
	addEdge(4, 5, 1);
	addEdge(5, 6, 1);
	addEdge(6, 7, 1);
	addEdge(7, 8, 1);
	int src = 0;//source node
	zeroOneBFS(src);
	return 0;
}
