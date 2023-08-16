#NOTE: This code is ONLY for binary trees
# for n-ary trees => see binary lifting



// Binary tree -> 2 nodes given ->find their LCA

//method 2 is better 


//method 1 -> make an array of paths from root->p1 and root->p2...then using those paths, find the last element from the start which is present in both of them

class Solution {
public:
    int flag=0;
    void dfs(TreeNode* root, TreeNode* x, vector<TreeNode*>&v)
    {
        if(root==NULL || flag==1)
            return;
        
        v.push_back(root);
        
        if(root==x)
        {
            flag=1;
            return;
        }
        
        if(root->left && flag==0)
            dfs(root->left,x,v);
        
        if(root->right && flag==0)
            dfs(root->right,x,v);
        
        if(flag==0)
            v.pop_back();
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*>path1,path2;
        
        flag=0;
        dfs(root,p,path1);
        flag=0;
        dfs(root,q,path2);        
        
        int count = -1;
        for(int i=0; i<path1.size() && i<path2.size(); i++)
        {
            if(path1[i] == path2[i]) 
                count++;
            else 
                break;
        }
                
        return count==-1 ? NULL : path1[count];
    }
};



//method 2

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL)
            return NULL;
        
        if(root==p || root==q)
            return root;
        
        TreeNode* l = lowestCommonAncestor(root->left, p, q);
        TreeNode* r = lowestCommonAncestor(root->right, p, q);
        
        if(l!=NULL && r!=NULL)
            return root;   //imp
        
        if(r!=NULL)
            return r;     //imp...not root
        if(l!=NULL)
            return l;    //imp...not root
        
        return NULL;
    }
};
