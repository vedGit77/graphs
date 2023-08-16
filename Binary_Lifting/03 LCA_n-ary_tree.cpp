// N <= 10000 (no of nodes)
// Q <= 10000 (no of queries)
// root of the tree will always be node 0


//Approach: we per-calculate depth of each node AND binary lifting table
//   	  : we bring both nodes (in current query) at same level -> how? -> since we know depth -> find diff in depth and use binary lifting
//        : now, using binary lifting -> find LCA



const int MAX_N = 10000;  //no.of nodes
const int LOG = 14;      // since (2^14 > MAX_N) OR log(10000)(base 2)

vector<vector<int>> children(MAX_N);  //adjacency list -> useful in dfs for finding depth
vector<int>parent(MAX_N);   //stores 1st parent of each node -> useful to pre-compute binary lifing table

int up[MAX_N][LOG]; // up[v][j] is 2^j-th ancestor of v => binary_lifting table
int depth[MAX_N];  //depth of each node from root

void dfs(int a)   //dfs ka work is to store the depth
{  
	for(int b : children[a]) {
		depth[b] = depth[a] + 1;
		dfs(b);
	}
}

void fill_up(){
	for(int i=0;i<MAX_N;i++)
		up[i][0] = parent[i];
	
	for(int j=1; j<LOG; j++){
		for(int i=0; i<MAX_N; i++){
			if(up[i][j-1] == -1)
				up[i][j] = -1;
			else
				up[i][j] = up[ up[i][j-1] ][j-1];
		}
	}
}

bool check(int k){
    int a = 0;
	
    for(int j = LOG; j >= 0; j--) {
	if(k & (1 << j)) 
		a = up[a][j]; // parent of a
    }
    
    int b = 1;
	
    for(int j = LOG; j >= 0; j--) {
	if(k & (1 << j)) 
		b = up[b][j]; // parent of a
    }

    return a == b;
}

int get_lca(int a, int b) { // O(log(N))
	if(depth[a] < depth[b]) {
		swap(a, b);
	}
	// 1) Get same depth.
	int k = depth[a] - depth[b];
	for(int j = LOG - 1; j >= 0; j--) {
		if(k & (1 << j)) {
			a = up[a][j]; // parent of a
		}
	}
	// 2) if b was ancestor of a then now a==b
	if(a == b) {
		return a;
	}
	// 3) move both a and b with powers of two
	for(int j = LOG - 1; j >= 0; j--) {
		if(up[a][j] != up[b][j]) { 
			a = up[a][j];
			b = up[b][j];
		}
	}
	return up[a][0];
}

int main() {
	int n;
	cin >> n;
	for(int v = 0; v < n; ++v) {
		int cnt;
		cin >> cnt;
		for(int i = 0; i < cnt; i++) {
			int c;
			cin >> c;
			children[v].push_back(c);  //directed graph banaya hai
			parent[c] = v;  //make parent array-> 1st parent of each node
		}
	}
	
	parent[0] = -1;  //IMP-> parent[0] = -1 -> same as binary lifting
	
	dfs(0); //given 0 is the root -> find depth of all nodes
	fill_up();  //fill 'up' table -> 'up' table used for binary lifting
	
	int q;
	cin >> q;
	for(int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		cout << get_lca(a, b) << "\n";
	}
}
