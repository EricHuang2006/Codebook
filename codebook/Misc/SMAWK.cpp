bool select(int r, int u, int v){
    // if f(r, v) is better than f(r, u), return true
	return f(r, u) < f(r, v);
}
// For all 2x2 submatrix: (x < y => y is better than x)
// If M[1][0] < M[1][1], M[0][0] < M[0][1]
// If M[1][0] == M[1][1], M[0][0] <= M[0][1]
// M[i][ans[i]] is the best value in the i-th row
vector<int> solve(vector<int> &r, vector<int> &c){
	if(r.size() == 1){
		vector<int> opt(1, 0);
		for(int i = 1; i < c.size(); i++){
			if(select(r[0], c[opt[0]], c[i])){
				opt[0] = i;
			}
		}
		return opt;
	}
	//reduce
	vector<int> st, rev;
	for(int i = 0; i < c.size(); i++){
		while(!st.empty() && select(r[st.size() - 1], st.back(), c[i])){
			st.pop_back();
			rev.pop_back();
		}
		if(st.size() < r.size()){
			st.pb(c[i]);
			rev.pb(i);
		}
	}
	//interpolate
	vector<int> half;
	for(int i = 0; i < r.size(); i += 2){
		half.pb(r[i]);
	}
	vector<int> ans(r.size());
	auto interp = solve(half, st);
	for(int i = 0; i < interp.size(); i++) ans[i * 2] = interp[i];
	for(int i = 1; i < ans.size(); i += 2){
		int s = ans[i - 1], e = (i + 1 < ans.size() ? ans[i + 1] : st.size() - 1);
		ans[i] = s;
		for(int j = s + 1; j <= e; j++){
			if(select(r[i], st[ans[i]], st[j])) ans[i] = j;
		}
	}
	for(int i = 0; i < ans.size(); i++) ans[i] = rev[ans[i]];
	return ans;
}

vector<int> smawk(int n, int m){
	vector<int> r(n), c(m);
	iota(r.begin(), r.end(), 0);
	iota(c.begin(), c.end(), 0);
	return solve(r, c);
}