void Gomory_Hu_Tree(vector<int> st){
	if(st.size() <= 1) return;
	int s = st[0], t = st[1];
	flow.init(n, s, t);
	for(auto [a, b, w] : e) flow.add_edge(a, b, w);
	int cost = flow.flow();
	flow.bfs();
	adj[s].eb(t, cost), adj[t].eb(s, cost);
	vector<int> a, b;
	for(auto x : st){
		if(flow.level[x] == -1) a.pb(x);
		else b.pb(x);
	}
	Gomory_Hu_Tree(a);
	Gomory_Hu_Tree(b);
}