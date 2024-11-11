int edge[maxn][maxn], par[maxn], siz[maxn];
int dist[maxn], vis[maxn], done[maxn];
int n, m;
int root(int x)
{ return x == par[x] ? x : par[x] = root(par[x]); }
int contract(int &s, int &t){
	memset(dist, 0, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	int mincut = INF, id, maxc;
	for(int i = 0; i < n; i++){
		id = maxc = -1;
		for(int j = 0; j < n; j++){
			if(!done[j] && !vis[j] && dist[j] > maxc){
				id = j;
				maxc = dist[j];
			}
		}
		if(id == -1) return mincut;
		s = t, t = id;
		mincut = maxc;
		vis[id] = true;
		for(int j = 0; j < n; j++){
			if(!done[j] && !vis[j]) dist[j] += edge[id][j];
		}
	}
	return mincut;
}
int Stoer_Wagner(){
	int mincut = INF, s, t, tmp;
	for(int i = 1; i < n; i++){
		tmp = contract(s, t);
		done[t] = true;
		mincut = min(mincut, tmp);
		if(!mincut) return 0;
		for(int j = 0; j < n; j++){
			if(!done[j]) edge[s][j] = (edge[j][s] += edge[j][t]);
		}
	}
	return mincut;
}
