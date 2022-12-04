//Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
//The distance between two adjacent cells is 1 (l,r,u,d directions allowed)

// ques link:
// https://leetcode.com/problems/01-matrix/
// similar ques:
// https://leetcode.com/problems/rotting-oranges/


// Approach-1:

//shortest paths-unweighted graph---->bfs(very standard)
//but usually 1 source node---minimum distance from that particular node
//but here multiple source nodes
//so push all of them first
//WHY???
//WHEN WE POP AND EXPLORE WE ARE DOING SO IN INCREASING ORDER OF THEIR LEVELS
//SO WHEN WE DISCOVER A NODE FIRST WE ARE EXPLORING IT FROM MINI POSSIBLE LEVEL NODE THAT IT IS CONNECTED TO
//first the source..then level 1 nodes..then level 2 and so on
//here the case is there are many level 0 nodes
//so push all of them first!!!


// Approach-2 :check 43rd file in dp repo

class Solution {
public:
    bool isvalid(int i,int j,int n,int m)
    {
        if(i==n||j==m||j<0||i<0)
            return false;
        return true;
    }
    
    vector<vector<int>> direction={{1,0},{0,1},{0,-1},{-1,0}};
    
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) 
    {
        queue<pair<int,int>> q;
        int n=matrix.size();
        int m=matrix[0].size();
        vector<vector<int>> ans(n,vector<int>(m,-1));
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(matrix[i][j]==0)
                { 
                    q.push({i,j});
                    ans[i][j]=0;
                }
            }
        }
        
        while(!q.empty())
        {
            pair<int,int> curr=q.front();
            q.pop();
            for(auto& x:direction)
            {
                int a=curr.first+x[0];
                int b=curr.second+x[1];
                if(isvalid(a,b,n,m) && ans[a][b]==-1)
                {
                    q.push({a,b}); //pushing the next levels into bfs queue....//like first we finished for all matrix[i][j]==0...then pushing all these zeroes ke neighbours...so on
                    ans[a][b] = ans[curr.first][curr.second] + 1;
                }
            }
        }
        return ans;
    }
};
