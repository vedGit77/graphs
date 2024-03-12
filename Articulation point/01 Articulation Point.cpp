//PRE-REQUISITE => Bridges in graph

// intro:
// A vertex in an UNdirected connected graph is an articulation point (or cut vertex) if removing it (and edges through it) disconnects the graph. 
// Articulation points represent vulnerabilities in a connected network – single points whose failure would split the network into 2 or more components. 
// They are useful for designing reliable networks. 
// For a disconnected undirected graph, an articulation point is a vertex removing which increases number of connected components.


// Naive soln:
// 1) For every vertex v, do following 
// …..a) Remove v from graph (from adjacency list/matrix)
// ..…b) See if the graph remains connected (We can either use BFS or DFS) 
// …..c) Add v back to the graph
// Time complexity of above method is O(V*(V+E)) for a graph




// Efficient soln: O(V+E)
// time array (tin) => same defn as bridge
// Lowest time (low) => current node goes to all its adjacent nodes EXCEPT the {parent} AND the {visited nodes} and takes the minimum lowest time

// so {low} array defn is diff => in bridges we exclude ONLY parent
// 			       => here we exclude parent AND visited nodes

//below => I will mark how algo is diff from bridges algo



#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int timer = 1;
    void dfs(int node, int parent, vector<int> &vis, int tin[], int low[], vector<int> &mark, vector<int>adj[]) {
        vis[node] = 1;
        tin[node] = low[node] = timer;
        timer++;
        int child = 0;    //diff 1 => create an extra variable
	    
        for (auto it : adj[node]) {
            if (it == parent) 
		continue;
            if (!vis[it]) {
                dfs(it, node, vis, tin, low, mark, adj);
                low[node] = min(low[node], low[it]);
                if (low[it] >= tin[node] && parent != -1) {    //diff 2 => ***tin[node]*** AND ***>=*** AND ***par!=-1***
                    mark[node] = 1;
                }
                child++;   //diff 3  => child++ ONLY when UN-visited
            }else{
                low[node] = min(low[node], tin[it]);   //diff 4 => upar use tin[node] => here use tin[it]
            }
        }
        if (child > 1 && parent == -1) {   //diff 5
            mark[node] = 1;
        }
    }
public:
    vector<int> articulationPoints(int n, vector<int>adj[]) {
        vector<int> vis(n, 0);
        int tin[n];
        int low[n];
        vector<int> mark(n, 0);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, -1, vis, tin, low, mark, adj);
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (mark[i] == 1) {
                ans.push_back(i);
            }
        }
        if (ans.size() == 0) return { -1};
        return ans;
    }
};
int main() {

    int n = 5;
    vector<vector<int>> edges = {
        {0, 1}, {1, 4},
        {2, 4}, {2, 3}, {3, 4}
    };

    vector<int> adj[n];
    for (auto it : edges) {
        int u = it[0], v = it[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Solution obj;
    vector<int> nodes = obj.articulationPoints(n, adj);
    for (auto node : nodes) {
        cout << node << " ";
    }
    cout << endl;
    return 0;
}

