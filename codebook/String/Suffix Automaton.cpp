struct SuffixAutomaton{
	int len[maxn], link[maxn]; // maxn >= 2 * n - 1
    map<char, int> nxt[maxn];
    int cnt[maxn], distinct[maxn];
	bool is_clone[maxn];
   	int first_pos[maxn];
   	vector<int> inv_link[maxn]; //suffix references
	int sz = 1, last = 0;
	void init(string s){
		link[0] = -1;
		for(auto x : s) sa_extend(x);
	}
	void sa_extend(char c){
		int cur = sz++;
        cnt[cur] = 1;
		len[cur] = len[last] + 1;
		first_pos[cur] = len[cur] - 1;
		int p = last;
		while(p != -1 && !nxt[p].count(c)){
			nxt[p][c] = cur;
			p = link[p];
		}
		if(p == -1) link[cur] = 0;
		else{
			int q = nxt[p][c];
			if(len[q] == len[p] + 1) link[cur] = q;
			else{
				int clone = sz++;
				is_clone[clone] = true;
				first_pos[clone] = q;
				len[clone] = len[p] + 1;
				nxt[clone] = nxt[q];
				link[clone] = link[q];
				while(p != -1 && nxt[p][c] == q) {
					nxt[p][c] = clone;
					p = link[p];
				}
				link[cur] = link[q] = clone;
			}
		}
		last = cur;
	}
	ll getDistinct(int pos){ // number of distinct substr. starting at pos(inc. empty)
		if(distinct[pos]) return distinct[pos];
		distinct[pos] = 1;
		for(auto [c, next] : nxt[pos]) distinct[pos] += getDistinct(next);
		return cnt[pos];
	}
	ll numDistinct(){
		return getDistinct(0) - 1; // excluding an empty string
	}
	ll numDistinct2(){
		ll tot = 0;
		for(int i = 1; i < sz; i++) tot += len[i] - len[link[i]];
		return tot;
	}
    void compute_cnt(){ // endpos set size
		vector<vector<int>> v(sz);
		for(int i = 1; i < sz; i++) v[len[i]].pb(i);
		for(int i = sz - 1; i > 0; i--) for(auto x : v[i]) {
			cnt[link[x]] += cnt[x];
		}
    }
	string distinct_kth(ll k){
        // substring kth (not distinct) -> compute_cnt()
		numDistinct();
		string s;
		ll cur = 0, tally = 0;
		while(tally < k){
			for(auto [c, next] : nxt[cur]){
				if(tally + distinct[next] >= k){
					tally += 1;
					s += c;
					cur = next;
					break;
				}
				tally += distinct[next];
			}
		}
		return s;
	}
	//inverse links
	void genLink(){
	    for(int i = 1; i < sz; i++){
            inv_link[link[i]].pb(i);
	    }
	}
	void get_all_occur(vector<int>& oc, int v){
	    if(!is_clone[v]) oc.pb(first_pos[v]);
	    for(auto u : inv_link[v]) get_all_occur(oc, u);
	}
	vector<int> all_occ(string s){ // get all occ of s
	    int cur = 0;
	    for(auto x : s){
	        if(!nxt[cur].count(x)) return {};
	        cur = nxt[cur][x];
	    }
	    vector<int> oc;
	    get_all_occur(oc, cur);
	    for(auto &x : oc) x += 1 - s.length(); // starting positions
	    sort(oc.begin(), oc.end());
	    return oc;
	}
	int lcs(string t){
		int v = 0, l = 0, ans = 0;
		for(auto x : t){
			while(v && !nxt[v].count(x)){
				v = link[v];
				l = len[v];
			}
			if(nxt[v].count(x)){
				v = nxt[v][x];
				l++;
			}
			ans = max(ans, l);
		}
		return ans;
	}
};