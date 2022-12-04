//ALSO IN THE DISJOINT SET PART!
//can also be used in cycle detection


// Below are the steps for finding MST using Kruskal’s algorithm
// 1. Sort all the edges in non-decreasing order of their weight. 
// 2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If cycle is not formed, include this edge. Else, discard it. 
// 3. Repeat step#2 until there are (V-1) edges in the spanning tree.

// Step #2 uses the Union-Find algorithm to detect cycles.
// The algorithm is a Greedy Algorithm. 
// The Greedy Choice is to pick the smallest weight edge that does not cause a cycle in the MST(min spanning tree) constructed so far. 

// Time complexity is O(E log V), V being the number of vertices.

#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> iPair;  // Creating shortcut for an integer pair

struct Graph
{
	int V, E;
	vector< pair<int, iPair> > edges;

	Graph(int V, int E)  //constructor
	{
		this->V = V;
		this->E = E;
	}

	void addEdge(int u, int v, int w)  	// Utility function to add an edge
	{
		edges.push_back({w, {u, v}});  //IMP...push_back(int,pair<int,int>)....push_back(weight,{src,destination})....so that we can sort by weight
	}

	int kruskalMST();
};

// To represent Disjoint Sets
struct DisjointSets
{
	int *parent, *rnk;
	int n;

	DisjointSets(int n) // Constructor
	{
		this->n = n;  // Constructor.
		parent = new int[n+1];
		rnk = new int[n+1];

		for (int i = 0; i <= n; i++)   
		{
			rnk[i] = 0;     // Initially, all vertices are in different sets and have rank 0.
			parent[i] = i;  //every element is parent of itself
		}
	}
	
	//both pathcompression and union by find are COMBINED in kruskal!!! => best time complexity

	int find(int u)  // Path Compression
	{
		if (u == parent[u])
			return parent[u];
		
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	void merge(int x, int y)    // Union by rank
	{
		x = find(x), y = find(y);

		if (rnk[x] > rnk[y])         //Make tree with smaller height a subtree of the other tree 
			parent[y] = x;
		else if(rnk[x] < rnk[y])
			parent[x] = y;
		else
		{
			parent[x] = y;
			rnk[y]++;
		}
	}
};


int Graph::kruskalMST()  /* Functions returns weight of the MST*/
{
	int mst_wt = 0; // Initialize result

	sort(edges.begin(), edges.end());  // Sort edges in increasing order on basis of cost

	//this disjoint set is mainly important
	DisjointSets ds(V); //create disjoint set....to create...all we need is a 'parent' and 'rank' array -> **IMP** -> No need to make struct

	vector< pair<int, iPair> >::iterator it;
	for (it=edges.begin(); it!=edges.end(); it++)  	// Iterate through all sorted edges
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.find(u);
		int set_v = ds.find(v);

		if (set_u != set_v)  //(Cycle is created if u and v belong to same set)
		{
			cout << u << " - " << v << endl;  // Current edge will be in the MST so print it

			mst_wt += it->first;

			ds.merge(set_u, set_v);  // Merge two sets....while merging...find parents....then compare RANK OF PARENTS!
		}
	}

	return mst_wt;
}

// Driver program to test above functions
int main()
{
	/* Let us create above shown weighted
	and undirected graph */
	int V = 9, E = 14;
	Graph g(V, E);

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

	cout << "Edges of MST are \n";
	int mst_wt = g.kruskalMST();

	cout << "\nWeight of MST is " << mst_wt;

	return 0;
}
