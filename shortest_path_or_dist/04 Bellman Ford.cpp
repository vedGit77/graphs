// works for: ((directed OR undirected) && cyclic graphs  &&  weighted  &&  -ive path distances)

// time complexity of Bellman-Ford is O(VE), which is more than Dijkstra. Only advantage over Dijkstra is the ability to handle -ive weights.


//SUPER IMP: 1. it works for -ive weights, BUT NOT for -ive weight CYCLES
//           2. Bellman-Ford does NOT work with UNdirected graph with negative edges as it will declared as negative cycle.


// Algorithm 
// Input: Graph and a source vertex src 
// Output: Shortest distance to all vertices from src. If there is a negative weight cycle, 
//         then shortest distances are not calculated, negative weight cycle is reported.
// 1) This step initializes distances from the source to all vertices as infinite and distance to the source itself as 0. 
//    Create an array dist[] of size |V| with all values as infinite except dist[src] where src is source vertex.
// 2) This step calculates shortest distances. Do following |V|-1 times where |V| is the number of vertices in given graph. 
// …..a) Do following for each edge u-v 
// ………………If dist[v] > dist[u] + weight of edge uv, then update dist[v] 
// ………………….dist[v] = dist[u] + weight of edge uv
// 3) This step reports if there is a negative weight cycle in graph. Do following for each edge u-v 
// ……If dist[v] > dist[u] + weight of edge uv, then “Graph contains negative weight cycle” 

#include <bits/stdc++.h> 

struct Edge { 
  	int src, dest, weight; 
}; 

struct Graph { 
    int V, E; 
    struct Edge* edge; 
}; 

struct Graph* createGraph(int V, int E) 
{ 
    struct Graph* graph = new Graph; 
    graph->V = V; 
    graph->E = E; 
    graph->edge = new Edge[E]; 
    return graph; 
} 

void printArr(int dist[], int n) 
{ 
    printf("Vertex Distance from Source\n"); 
    for (int i = 0; i < n; ++i) 
        printf("%d \t\t %d\n", i, dist[i]); 
} 

void BellmanFord(struct Graph* graph, int src) 
{ 
    int V = graph->V; 
    int E = graph->E; 
    int dist[V]; 

    for (int i = 0; i < V; i++) 
      dist[i] = INT_MAX; 
  
    dist[src] = 0; 

    for (int i = 1; i <= V - 1; i++) 
    { 
	      for (int j = 0; j < E; j++) 
	      {
			int u = graph->edge[j].src; 
			int v = graph->edge[j].dest; 
			int weight = graph->edge[j].weight; 

			if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) 
			    dist[v] = dist[u] + weight; 
	      } 
    } 

    for (int i = 0; i < E; i++) 
    { 
		int u = graph->edge[i].src; 
		int v = graph->edge[i].dest; 
		int weight = graph->edge[i].weight; 

		if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) //obvio logic...always true if we have a -ive weight cycle
		{ 						 //(dist[u] + weight < dist[v]) will always be true...thus dist[v] will keep on decreasing
			    printf("Graph contains negative weight cycle"); 
			    return; 
		} 
    } 

    printArr(dist, V); 

    return; 
} 

int main() 
{ 
    int V = 4;
    int E = 5; 
    struct Graph* graph = createGraph(V, E); 

    // add edge 0-1 (or A-B) 
    graph->edge[0].src = 0; 
    graph->edge[0].dest = 1; 
    graph->edge[0].weight = 1; 

    // add edge 0-2 (or A-C) 
    graph->edge[1].src = 0; 
    graph->edge[1].dest = 2; 
    graph->edge[1].weight = 4; 

    // add edge 1-2 (or B-C) 
    graph->edge[2].src = 1; 
    graph->edge[2].dest = 2; 
    graph->edge[2].weight = -3; 

    // add edge 1-3 (or B-D) 
    graph->edge[3].src = 1; 
    graph->edge[3].dest = 3; 
    graph->edge[3].weight = 2; 

    // add edge 2-3 (or C-D) 
    graph->edge[4].src = 2; 
    graph->edge[4].dest = 3; 
    graph->edge[4].weight = 3; 

    BellmanFord(graph, 0); 

	  return 0; 
} 
