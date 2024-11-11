namespace AC{
	int ch[maxn][26], fail[maxn], idx[maxn], last[maxn], pt[maxn];
	int val[maxn], cnt[maxn], tot = 0;
    // val[i] = # of times node(i) is visited, cnt[i] = # of occ. of str(i)
	void init(){
		memset(ch, 0, sizeof(ch)), memset(fail, 0, sizeof(fail));
		memset(idx, 0, sizeof(idx)), memset(last, 0, sizeof(last));
		memset(val, 0, sizeof(val)), memset(cnt, 0, sizeof(cnt));
		tot = 0;
	}
	void insert(string &s, int id){ // id is 1-based
		int cur = 0;
		for(int i = 0; i < s.size(); i++){
			if(!ch[cur][s[i] - 'a']) ch[cur][s[i] - 'a'] = ++tot;
			cur = ch[cur][s[i] - 'a'];
		}
		if(idx[cur] == 0) idx[cur] = id;
		else pt[id] = idx[cur];
	}
	void build(){
		queue<int> q;
		for(int i = 0; i < 26; i++){
			if(ch[0][i]) q.push(ch[0][i]);
		}
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(int i = 0; i < 26; i++){
				if(ch[u][i]) {
					fail[ch[u][i]] = ch[fail[u]][i];
					q.push(ch[u][i]);
				}
				else ch[u][i] = ch[fail[u]][i];
				last[ch[u][i]] = idx[fail[ch[u][i]]] ? fail[ch[u][i]] : last[fail[ch[u][i]]];
			}
		}
	}
	int qry(string &s){ 
		int u = 0, ret = 0;
		for(int i = 0; i < s.size(); i++){
			u = ch[u][s[i] - 'a'];
			for(int j = u; j; j = last[j]) val[j] ++;
		}
		for(int i = 0; i <= tot; i++){
			if(idx[i]) ret = max(ret, val[i]), cnt[idx[i]] = val[i];
		}
		return ret;
	}
};