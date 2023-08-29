// UN-directed and connected graph
// count cycles of length n

// time complexity: O(V*V)

// APPROACH:
// Using DFS we find every possible path of length (n-1) for a particular source (or starting point). 
// Then we check if this path ends with the vertex it started with, if yes then we count this as the cycle of length n.




// Number of vertices
const int V = 5;

void DFS(bool graph[][V], bool marked[], int n, int vert, int start, int& count)
{
	// mark the vertex vert as visited
	marked[vert] = true;

	// if the path of length (n-1) is found
	if (n == 0) {
		// mark vert as un-visited to make it usable again.
		marked[vert] = false;

		// Check if vertex vert can end with vertex start
		if (graph[vert][start] && graph[start][vert]) 
			count++;
		
		return;
	}

	// For searching every possible path of length (n-1)
	for (int i = 0; i < V; i++){
		if (!marked[i] && graph[vert][i])
			// DFS for searching path by decreasing length by 1
			DFS(graph, marked, n - 1, i, start, count);
	}

	// marking vert as unvisited to make it usable again.
	marked[vert] = false;
}

// Counts cycles of length N in an undirected and connected graph.
int countCycles(bool graph[][V], int n)
{
	// all vertex are marked un-visited initially.
	bool marked[V];
	memset(marked, 0, sizeof(marked));

	int count = 0;
	for (int i = 0; i < V; i++) {
		DFS(graph, marked, n - 1, i, i, count);
		// ith vertex is marked as visited and will not be visited again.
		marked[i] = true;
	}

	return count / 2;  //since every vertex -> finds 2 duplicate cycles that it forms. example 0th vertex => 0->1->2 and 0->2->1 (for a cycle of length 3)
}

int main()
{
	bool graph[][V] = { { 0, 1, 0, 1, 0 },
				{ 1, 0, 1, 0, 1 },
				{ 0, 1, 0, 1, 0 },
				{ 1, 0, 1, 0, 1 },
				{ 0, 1, 0, 1, 0 } };
	
	int n = 4;  //length of cycle
	cout << "Total cycles of length " << n << " are "<< countCycles(graph, n);
	return 0;
}
