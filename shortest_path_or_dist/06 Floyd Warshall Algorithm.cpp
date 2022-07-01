//Floyd Warshall Algorithm....Graphs + DP

// The problem is to find shortest distances between every pair of vertices in a given edge weighted directed Graph. 

//EXAMPLE:
// Input:
//        graph[][] = { {0,   5,  INF, 10},
//                     {INF,  0,  3,  INF},
//                     {INF, INF, 0,   1},
//                     {INF, INF, INF, 0} }
// which represents the following graph
//              10
//        (0)------->(3)
//         |         /|\
//       5 |          |
//         |          | 1
//        \|/         |
//        (1)------->(2)
//             3       
// Note that the value of graph[i][j] is 0 if i is equal to j 
// And graph[i][j] is INF (infinite) if there is no edge from vertex i to j.

// Output:
// Shortest distance matrix
//       0      5      8      9
//     INF      0      3      4
//     INF    INF      0      1
//     INF    INF    INF      0




// Floyd Warshall Algorithm 
// 1. We initialize the solution matrix same as the input graph matrix as a first step.
// 2.Then we update the solution matrix by considering all vertices as an intermediate vertex. 
//   The idea is to one by one pick all vertices and update all shortest paths which include the picked vertex as an intermediate vertex in the shortest path. 
//   When we pick vertex number k as an intermediate vertex, we already have considered vertices {0, 1, 2, .. k-1} as intermediate vertices. 
//   For every pair (i, j) of the source and destination vertices respectively, there are two possible cases:
// 
// a) k is not an intermediate vertex in shortest path from i to j. We keep the value of dist[i][j] as it is. 
// b) k is an intermediate vertex in shortest path from i to j. 
//    We update the value of dist[i][j] as dist[i][k] + dist[k][j] if dist[i][j] > dist[i][k] + dist[k][j]

	

#include <bits/stdc++.h>
using namespace std;

#define V 4
#define INF 99999

/* A utility function to print solution */
void printSolution(int dist[][V])
{
	cout << "The following matrix shows the shortest "
			"distances"
			" between every pair of vertices \n";
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				cout << "INF"
					<< "	 ";
			else
				cout << dist[i][j] << "	 ";
		}
		cout << endl;
	}
}

// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshall(int graph[][V])
{
	int dist[V][V]; //this will be our final ans
	int i, j, k;

	for (i = 0; i < V; i++) // Initialize the solution matrix same as input graph matrix. 
		for (j = 0; j < V; j++)
			dist[i][j] = graph[i][j];

	/*Before start of an iteration, we have shortest distances between all
	pairs of vertices such that the shortest distances consider only the
	vertices in set {0, 1, 2, .. k-1} as intermediate vertices.*/
	
	for (k = 0; k < V; k++) //start with OUTER LOOP OF K
	{  
		for (i = 0; i < V; i++)  // Pick all vertices as source one by one
		{
			for (j = 0; j < V; j++) // Pick all vertices as destination for the above picked source
			{
				// If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
				if ( dist[i][j] > (dist[i][k] + dist[k][j]) //condition-1
				    && (dist[k][j] != INF && dist[i][k] != INF)) //condition-2
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	printSolution(dist); //print the shortest dist
}

// Driver code
int main()
{
	 /* Let us create the following weighted graph
            10
    (0)------->(3)
     |       /|\
   5 |        |
     |        | 1
    \|/       |
    (1)------->(2)
            3     */
	int graph[V][V] = { { 0, 5, INF, 10 },
			{ INF, 0, 3, INF },
			{ INF, INF, 0, 1 },
			{ INF, INF, INF, 0 } };

	// Print the solution
	floydWarshall(graph);
	return 0;
}


