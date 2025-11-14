int in[maxn], id[maxn], par[maxn], dfn = 0;
int mn[maxn], idom[maxn], sdom[maxn], ans[maxn];
int fa[maxn]; // dsu
int n, m;
vector<int> adj[3][maxn];

void dfs(int pos){
	in[pos] = ++dfn;
	id[dfn] = pos;
	for(auto x : adj[0][pos]){
		if(in[x]) continue;
		par[x] = pos;
		dfs(x);
	}
}

int find(int x){
	if(fa[x] == x) return x;
	int tmp = fa[x];
	fa[x] = find(fa[x]);
	if(in[sdom[mn[tmp]]] < in[sdom[mn[x]]]){
		mn[x] = mn[tmp];
	}
	return fa[x];
}

void tar(int st){
	dfs(st);
    idom[st] = st;
	for(int i = 0; i < n; i++){
        if(!in[i]) idom[i] = -1;
        else mn[i] = sdom[i] = fa[i] = i;
    }
	for(int i = dfn; i >= 2; i--){
		int pos = id[i], res = INF; // res : in(x) of sdom
		for(auto x : adj[1][pos]){
			if(!in[x]) continue;
			find(x);
			if(in[pos] > in[x]) res = min(res, in[x]);
			else res = min(res, in[sdom[mn[x]]]);
		}
		sdom[pos] = id[res];
		fa[pos] = par[pos];
		adj[2][sdom[pos]].pb(pos);
		pos = par[pos]; 
		for(auto x : adj[2][pos]){
			find(x);
			if(sdom[mn[x]] == pos){
				idom[x] = pos;
			}
			else{
				idom[x] = mn[x];
			}
		}
		adj[2][pos].clear();
	}
	for(int i = 2; i <= dfn; i++){
		int x = id[i];
		if(idom[x] != sdom[x]) idom[x] = idom[idom[x]];
	}
}