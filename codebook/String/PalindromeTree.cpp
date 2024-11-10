struct EERTREE{
	int sz, tot, last;
	int cnt[maxn], ch[maxn][26], len[maxn], fail[maxn], dif[maxn], slink[maxn];
	int g[maxn], dp[maxn];
	char s[maxn];
	int node(int l){
		sz++;
		memset(ch[sz], 0, sizeof(ch[sz]));
		len[sz] = l;
		fail[sz] = cnt[sz] = 0;
		return sz;
	}
	void init(){
		sz = -1;
		last = 0;
		s[tot = 0] = '$';
		node(0);
		node(-1);
		fail[0] = 1;
	}
	int getfail(int x){
		while(s[tot - len[x] - 1] != s[tot]) x = fail[x];
		return x;
	}
	void insert(char c){
		s[++tot] = c;
		int now = getfail(last);
		if(!ch[now][c - 'a']){
			int x = node(len[now] + 2);
			fail[x] = ch[getfail(fail[now])][c - 'a'];
			ch[now][c - 'a'] = x;
			dif[x] = len[x] - len[fail[x]];
			if(dif[x] == dif[fail[x]]){
				slink[x] = slink[fail[x]];
			}
			else slink[x] = fail[x];
		}
		last = ch[now][c - 'a'];
		cnt[last]++;
	}
	int process(string s){
		for(int i = 0; i < s.size(); i++){
			insert(s[i]);
			dp[i] = INF;
			for(int x = last; x > 1; x = slink[x]){
				if(i - len[slink[x]] - dif[x] >= 0) g[x] = dp[i - len[slink[x]] - dif[x]];
				if(dif[x] == dif[fail[x]]) g[x] = min(g[x], g[fail[x]]);
				dp[i] = min(dp[i], g[x] + 1);
			}
		}
		return dp[s.size() - 1];
	}
} pam;