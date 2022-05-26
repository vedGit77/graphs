// question link:
// https://leetcode.com/problems/number-of-islands/

// explanation video:
// https://www.youtube.com/watch?v=hVFFWpSRY4o

class Solution {
public:
    void dfs(vector<vector<char>>& grid,vector<vector<bool>>& visited, int i, int j)
    {
        if(i<0 || j<0 || i>=grid.size() || j>=grid[0].size())  //base conditions...VVIMP...THIS MUST COME BEFORE THE 2nd BASE CONDN.
            return;
        if(visited[i][j]==true || grid[i][j]=='0')  //IMP base conditions..if '0', then return....or if visited, then return
            return;
        
        visited[i][j]=true;  //obvio
        
        //since we DONT have any adjacency list...no need to iterate...here, our dfs modifies...we can move top,down,left,right....applied them below
        
        dfs(grid,visited,i+1,j);
        dfs(grid,visited,i,j+1);
        dfs(grid,visited,i-1,j);
        dfs(grid,visited,i,j-1);
    }
    int numIslands(vector<vector<char>>& grid) {
        
        int n = grid.size();
        int m = grid[0].size();
        
        vector<vector<bool>>visited(n , vector<bool>(m,false));  //this is how we initialize a 2d vector with n rows, m columns
        
        int count=0;  //to count no. of islands
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(!visited[i][j] && grid[i][j]=='1')  //IMP...apply DFS ONLY when grid[i][j]=='1', and not visited
                {
                    dfs(grid,visited,i,j);
                    count++;  // this part...apply loops and count++...similar to counting no of disconnected graphs/islands...like normal dfs
                }
            }
        }
        
        return count;
    }
};
