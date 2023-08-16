#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10000;
const int LOG = 14;
vector<vector<int>> children(MAX_N);
vector<int>parent(MAX_N);
int up[MAX_N][LOG]; // up[v][j] is 2^j-th ancestor of v
int depth[MAX_N];

void dfs(int a) {  //dfs ka work is to store the depth
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
		if(k & (1 << j)) {
			a = up[a][j]; // parent of a
		}
	}
	int b = 1;
    for(int j = LOG; j >= 0; j--) {
		if(k & (1 << j)) {
			b = up[b][j]; // parent of a
		}
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
			parent[c] = v;
		}
	}
	
	parent[0] = -1;
	
	dfs(0); //given 0 is the root
	fill_up();  //fill up table
	
	int q;
	cin >> q;
	for(int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		cout << get_lca(a, b) << "\n";
	}
}
