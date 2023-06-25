// On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at most one stone.

// A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.
means that if 1 stone is @ (0,0) and the other one is @ (100,0), then also 1 of them will be removed.

// Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone, 
// return the largest possible number of stones that can be removed.

// Example :
// Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
// Output: 5
// Explanation: One way to remove 5 stones is as follows:
// 1. Remove stone [2,2] because it shares the same row as [2,1].
// 2. Remove stone [2,1] because it shares the same column as [0,1].
// 3. Remove stone [1,2] because it shares the same row as [1,0].
// 4. Remove stone [1,0] because it shares the same column as [0,0].
// 5. Remove stone [0,1] because it shares the same row as [0,0].
// Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.


// SOLUTION:

// One sentence to solve:
// Connected stones can be reduced to 1 stone,
// the maximum stones can be removed = stones number - islands number.
// so just count the number of "islands".


// 1. Connected stones
// Two stones are connected if they are in the same row or same col.
// Connected stones will build a connected graph.
// It's obvious that in one connected graph,
// we can't remove all stones.

// We have to have one stone left.
// An intuition is that, in the best strategy, we can remove until 1 stone.

// I guess you may reach this step when solving the problem.
// But the important question is, how?


// 2. A failed strategy
// Try to remove the least degree stone
// Like a tree, we try to remove leaves first.
// Some new leaf generated.
// We continue this process until the root node left.

// However, there can be no leaf.
// When you try to remove the least in-degree stone,
// it won't work on this "8" like graph:
// [[1, 1, 0, 0, 0],
// [1, 1, 0, 0, 0],
// [0, 1, 1, 0, 0],
// [0, 0, 1, 1, 1],
// [0, 0, 0, 1, 1]]

// The stone in the center has least degree = 2.
// But if you remove this stone first,
// the whole connected stones split into 2 parts,
// and you will finish with 2 stones left.
  

// 3. A good strategy: Count the number of islands
// We call a connected graph as an island.
// One island must have at least one stone left.
// The maximum stones can be removed = stones number - islands number

// The whole problem is transferred to:
// What is the number of islands?

// You can show all your skills on a DFS implementation,
// and solve this problem as a normal one.


// 4. Search on the index, not the points
// When we search on points,
// we alternately change our view on a row and on a col.

// We think:
// a row index, connect two stones on this row
// a col index, connect two stones on this col.

// In another view：
// A stone, connect a row index and col.

// Have this idea in mind, the solution can be much simpler.
// The number of islands of points,
// is the same as the number of islands of indexes.


// 5. Union-Find
// I use union find to solve this problem.
// As I mentioned, the elements are not the points, but the indexes.

// a. for each point, union two indexes.
// b. return (points number - union number)


// Complexity
// union and find functions have worst case O(N), amortize O(1)
// The whole union-find solution with path compression,
// has O(N) Time, O(N) Space


// APPROACH_1 =>

class Solution {
public:
     int removeStones(vector<vector<int>>& stones) {
        for (int i = 0; i < stones.size(); ++i)
            uni(stones[i][0], ~stones[i][1]);   //why negation ???? => to make x and y coordinates in diff dimensions => we know : [ ~a = -(a+1) ]
                                                //earlier 0 <= x, y <= 10^4  => now x ka range is same => -10^4 -1 <= y <= -1
        return stones.size() - islands;
    }

    unordered_map<int, int> f;
    int islands = 0;

    int find(int x) {
        if (!f.count(x))
        {
            f[x] = x; 
            islands++;
        }
        if (x != f[x]) 
            f[x] = find(f[x]);
        
        return f[x];
    }

    void uni(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) 
        {
            f[x] = y;
            islands--;
        }
    }
};


// APPROACH_2 =>


class Solution {
public:
    void dfs(vector<int> adj[],vector<bool>& visited,int i)
    {
        if(visited[i])
            return;
        visited[i]= true;
        
        for(int u: adj[i])
        {
            if(!visited[u])
                dfs(adj,visited,u);
        }
    }
    
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        vector<int> adj[n];
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i!=j)
                {
                    if(stones[i][0]==stones[j][0] || stones[i][1]==stones[j][1])
                    {
                        adj[i].push_back(j);
                    }
                }
            }
        }
        
        vector<bool>visited(n,false);
        
        int count=0;
        for(int k=0;k<n;k++)
        {
            if(!visited[k])
            {
                dfs(adj,visited,k);  
                count++;
            }
        }
        
        return (n-count);
    }
};
