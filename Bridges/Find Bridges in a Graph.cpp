//both articulation pts and bridges are for an UNdirected graph

// An edge in an UNdirected connected graph is a bridge if removing it disconnects the graph. 
// For a disconnected undirected graph, definition is similar, a bridge is an edge removing which increases number of disconnected components. 
// Like Articulation Points, bridges represent vulnerabilities in a connected network and are useful for designing reliable networks


// Naive soln:
// 1) For every edge (u, v), do following 
// …..a) Remove (u, v) from graph(adjacency list/matrix)
// ..…b) See if the graph remains connected (We can either use BFS or DFS) 
// …..c) Add (u, v) back to the graph.
// Time complexity of above method is O(E*(V+E)) for a graph represented using adjacency list. 


// Efficient solution:
// O(V+E) time
// Time of insertion (tin): Dring DFS => time when a node is visited
// Lowest time (low): current node goes to all its adjacent nodes EXCEPT the parent and takes the MIN LOWEST TIME.


#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int timer = 1;  //global

    void dfs(int node, int parent, vector<int> &vis,  vector<int> adj[], int tin[], int low[], vector<vector<int>> &bridges) {
        vis[node] = 1;
        tin[node] = low[node] = timer;
        timer++;
        for (auto it : adj[node]) {
            if (it == parent)  //ignore parent
		    continue;
            if (vis[it] == 0){  //adj node not visited
                dfs(it, node, vis, adj, tin, low, bridges);
                low[node] = min(low[it], low[node]);  //min from low array
                
	        if (low[it] > tin[node])  //condn for bridge
                    bridges.push_back({it, node});
            }else{
                low[node] = min(low[node], low[it]);   //only update low (if already visited)
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n,
    vector<vector<int>>& connections) {
        vector<int> adj[n];
        for (auto it : connections) {
            int u = it[0], v = it[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> vis(n, 0);
        int tin[n];
        int low[n];
        vector<vector<int>> bridges;
        dfs(0, -1, vis, adj, tin, low, bridges);
        return bridges;
    }
};

int main() {

    int n = 4;
    vector<vector<int>> connections = {
        {0, 1}, {1, 2},
        {2, 0}, {1, 3}
    };

    Solution obj;
    vector<vector<int>> bridges = obj.criticalConnections(n, connections);
    for (auto it : bridges) {
        cout << "[" << it[0] << ", " << it[1] << "] ";
    }
    cout << endl;
    return 0;
}

