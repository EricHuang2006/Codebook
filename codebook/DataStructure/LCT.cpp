struct LCT{
	int ch[maxn][2], par[maxn], rev[maxn], xr[maxn], val[maxn];
	int get(int x){ return ch[par[x]][1] == x;}
	int isroot(int x){ return ch[par[x]][0] != x && ch[par[x]][1] != x;}
	void push(int x){
		if(rev[x]){
			if(rs) swap(ch[rs][0], ch[rs][1]), rev[rs] ^= 1;
			if(ls) swap(ch[ls][0], ch[ls][1]), rev[ls] ^= 1;
			rev[x] = 0;
		}
	}
	void pull(int x){
		xr[x] = xr[ls] ^ xr[rs] ^ val[x];
	}
	void rotate(int x){
		int y = par[x], z = par[y], k = get(x);
		if(!isroot(y)) ch[z][ch[z][1] == y] = x;
		ch[y][k] = ch[x][!k], par[ch[x][!k]] = y;
		ch[x][!k] = y, par[y] = x;
		par[x] = z;
		pull(y), pull(x);
	}
	void update(int x){
		if(!isroot(x)) update(par[x]);
		push(x);
	}
	void splay(int x){
		update(x); 
		for(int p = par[x]; !isroot(x); rotate(x), p = par[x]){
			if(!isroot(p)) rotate(get(p) == get(x) ? p : x);
		}
	}
	void access(int x){
		for(int p = 0; x != 0; p = x, x = par[x]){
			splay(x); 
			ch[x][1] = p; 
			pull(x);
		}
	}
	void make_root(int x){
		access(x);
		splay(x);
		swap(ls, rs);
		rev[x] ^= 1;
	}
	void link(int x, int y){
		make_root(x);
		splay(x);
		if(find_root(y) == x) return;
		par[x] = y;
	}
	void cut(int x, int y){
		make_root(x);
		access(y);
		splay(x);
		if(par[y] != x || ch[y][0]) return;
		ch[x][1] = par[y] = 0;
	}
	int find_root(int x){
		access(x);
		splay(x);
		push(x);
		while(ls) x = ls, push(x);
		splay(x); 
		return x;
	}
	void split(int x, int y){
		make_root(x);
		access(y);
		splay(y);
	}
	void upd(int x, int y){
		access(x);
		splay(x);
		val[x] = y;
		pull(x);
	}
} st;