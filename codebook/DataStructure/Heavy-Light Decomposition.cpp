int n, q, dfn = 0;
int val[maxn], sz[maxn], head[maxn], dep[maxn], st[maxn * 4], par[maxn], loc[maxn], id[maxn];
vector<int> adj[maxn];
 
void dfs(int pos, int prev){
	sz[pos] = 1;
	if(prev != -1) adj[pos].erase(find(adj[pos].begin(), adj[pos].end(), prev));
	for(auto &x : adj[pos]){
		par[x] = pos, dep[x] = dep[pos] + 1;
		dfs(x, pos);
		sz[pos] += sz[x];
		if(sz[x] > sz[adj[pos][0]]) swap(x, adj[pos][0]);
	}
}
void decompose(int pos, int h){
	id[dfn++] = pos;
	head[pos] = h, loc[pos] = dfn - 1;
	// upd(loc[pos], val[pos]);
	for(auto x : adj[pos]){
		if(x == adj[pos][0]) decompose(x, h);
		else decompose(x, x);
	}
}
void build(){
	dfs(0, -1);
	decompose(0, 0);
	//build_segtree();
}
int solve(int a, int b){
	int ret = 0;
	while(head[a] != head[b]){
		if(dep[head[a]] > dep[head[b]]) swap(a, b);
		ret = max(ret, qry(loc[head[b]], loc[b]));
		b = par[head[b]];
	}
	if(dep[a] > dep[b]) swap(a, b);
	return max(ret, qry(loc[a], loc[b])); 
}