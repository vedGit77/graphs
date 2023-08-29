// UNdirected graph
// 2 <= n <= 1000
// 1 <= edges.length <= 1000
// There are no repeated edges

// find shortest cycle length

//approach->
// apply BFS from every node -> find smallest cycle length starting and ending at that node
// do this for every node and find minimum cycle length

//time : O(V * (V+E))


class Solution {
public:
    int fun(int st, vector<vector<int>>&adj){
        int ret = INT_MAX, n = adj.size(), cnt = 0;

        queue<int>q;
        vector<int>dist(n, INT_MAX);
        vector<int>parent(n, -1);

        q.push(st);
        dist[st] = 0;

        while(q.size()>0){
            int node = q.front(), par = parent[node];
            q.pop();

            for(auto x:adj[node]){
                if(dist[x]!=INT_MAX && x!=par){
                    ret = min(ret, dist[node]+dist[x]+1);
                }else if(dist[x]==INT_MAX){
                    dist[x] = dist[node]+1;
                    parent[x] = node;
                    q.push(x);
                }
            }
        }

        return ret;
    }

    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>>adj(n);

        for(auto x:edges){
            adj[x[0]].push_back(x[1]);
            adj[x[1]].push_back(x[0]);
        }

        int ans = INT_MAX;

        for(int i=0;i<n;i++)
            ans = min(ans, fun(i, adj));

        return ans==INT_MAX ? -1 : ans;
    }
};
