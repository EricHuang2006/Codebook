struct Dinic{
	struct edge{
		ll to, cap;
		edge(){}
		edge(int _to, ll _cap) : to(_to), cap(_cap){}
	};
	vector<edge> e;
	vector<vector<int>> adj;
	vector<int> iter, level;
	int n, s, t;
	void init(int _n, int _s, int _t){
		n = _n, s = _s, t = _t;
		adj = vector<vector<int>>(n);
		iter = vector<int>(n);
		level = vector<int>(n);
		e.clear();
	}
	void add_edge(int from, int to, ll cap){
		adj[from].pb(e.size()), adj[to].pb(e.size() + 1);
		e.pb(edge(to, cap)), e.pb(edge(from, 0));
	}
	void bfs(){
		fill(level.begin(), level.end(), -1);
		level[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int cur = q.front(); q.pop();
			for(auto id : adj[cur]){
				auto [to, cap] = e[id];
				if(level[to] == -1 && cap){
					level[to] = level[cur] + 1;
					q.push(to);
				}
			}
		}
	}
	ll dfs(int pos, ll flow){
		if(pos == t) return flow;
		for(int &i = iter[pos]; i < adj[pos].size(); i++){
			auto [to, cap] = e[adj[pos][i]];
			if(level[to] == level[pos] + 1 && cap){
				ll tmp = dfs(to, min(flow, cap));
				if(tmp){
					e[adj[pos][i]].cap -= tmp;
					e[adj[pos][i] ^ 1].cap += tmp;
					return tmp; 
				}
			}
		}
		return 0;
	}
} flow;
