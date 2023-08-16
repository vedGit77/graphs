// Question:
// Given a vertex V of an N-ary tree and an integer K, 
// the task is to print the Kth ancestor/parent of the given vertex in the tree. 
// If there does not exist any such ancestor then print -1.

// Approach:
// technique is based on the fact that every integer can be represented in binary form. 
// Through pre-processing, a sparse table table[v][i] can be calculated 
// which stores the 2^i parent of the vertex v where 0 <= i <= logN(base 2)
// This pre-processing takes O(N*logN) time. 

// To find the Kth parent of the vertex V, 
// let K = b0b1b2…bn be an n bit number in the binary representation, 
// let p1, p2, p3, …, pj be the indices where bit value is 1 
// then K can be represented as K = 2^p1 + 2^p2 + 2^p3 + … + 2^pj. 
// Thus to reach Kth parent of V, we have to make jumps to 2^p1, 2^p2, 2^p3 upto 2^pj parent in any order. 
// This can be done efficiently through the sparse table calculated earlier in O(logN).


#VVIMP => on most websites => code is given with an assumption => (i > parent[i])

#NOTE: We have written a robust code => does NOT depend on any such inequality




TreeAncestor => Initializes the object with the n (number of nodes) in the tree and the (parent array)
getKthAncestor => return the kth ancestor of the given node node. If there is no such ancestor, return -1.
1 <= k <= n <= 50,000 => thus max power of 2 required is 20, since 2^20 > 50,000


class TreeAncestor {
public:
    vector<vector<int>>v;  //parent array => we will use precomputation on this
    //v[x][i] = 2^i ancestor of node x => IMP => 2^i and NOT i

    TreeAncestor(int n, vector<int>& parent) {  //parent array is given => 1st parent of each node
        vector<vector<int>> par(n, vector<int>(20));
        
        for (int i = 0; i < n; i++) 
            par[i][0] = parent[i];  //2^0 OR 1st parent of each node

        //IMP!!! => OUTER loop is for 2^j ancestor => calculate 2^j ancestor for each node, and then j++
        //if outer loop was 'i', and inner loop was 'j' => calculates all ancestors for a node, then i++ => works ONLY when (i > parent[i)
        for (int j = 1; j < 20; j++) {  
            for (int i = 0; i < n; i++) {
                if (par[i][j - 1] == -1)  //obvio
                    par[i][j] = -1;
                else 
                    par[i][j] = par[par[i][j - 1]][j - 1]; //IMP && obvio  => par[i][j] = 2^j parent of node i
            }
        }
        
        v = par;  //v and par are same => just that v is global
    }

    int getKthAncestor(int node, int k) {
        for (int i = 0; i < 20; i++) //imp=> start from 0
        {  
            if ((k >> i) & 1)  //since we check only where the binary representation has a set bit
            {  
                node = v[node][i];  //VVIMP => update node
                if (node == -1)  //obvio
                    return -1;
            }
        }
      
        return node;
    }
};



