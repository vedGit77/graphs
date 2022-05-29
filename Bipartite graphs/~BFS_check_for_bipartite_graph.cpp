//Logic:
// We have 2 colour codes: 0 and 1
// say we start with colouring our starting node with colour 1
// then we will do bfs traversal....and colour all the adjacent nodes of the starting node with colour 0
// then we will colour their adjacents with colour 1 ...so on....
// if at some instance we find an adjacent node, thats already coloured, but with the SAME colour...then NOT bipartite 


#include <bits/stdc++.h>
using namespace std;

bool bipartiteBfs(int src, vector<int> adj[], int color[]) 
{
    queue<int>q;
    q.push(src); 
    color[src] = 1; //our assumption.....always starting node is of colour code 1
    while(!q.empty()) 
    {
        int node = q.front(); 
        q.pop();
        
        for(auto it : adj[node]) 
        {
            if(color[it] == -1) 
            {
                color[it] = 1 - color[node]; //if colour[node]==1, then colour[it]=0 .... if colour[node]==0, then colour[it]=1
                q.push(it); 
            } 
            else if(color[it] == color[node]) //if already coloured/visited && same colour
            {
                return false; 
            }
        }
    }
    return true; 
}


bool checkBipartite(vector<int> adj[], int n) 
{
    int color[n]; //colour array storing the colour of all the nodes
    memset(color, -1, sizeof color); //initialize with -1
  
    for(int i = 0;i<n;i++) //for loop for disconnected graphs
    {
        if(color[i] == -1) //means unvisited..here colour also plays the role of visited array!
        {
            if(bipartiteBfs(i, adj, color)==false) 
            {
                return false;
            }
        }
    }
    return true; 
}

int main() 
{
    int n, m;
    cin >> n >> m;
    vector<int> adj[n];
    for(int i = 0;i<m;i++) 
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }

    if(checkBipartite(adj, n)) {
        cout << "yes"; 
    } else {
        cout << "No"; 
    }
    return 0;
}
