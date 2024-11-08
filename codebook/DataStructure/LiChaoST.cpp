struct line{
	ll m, k;
	line(){}
	line(ll _m, ll _k) : m(_m), k(_k){}
	ll val(ll x){ return m * x + k; }
}; 

struct node{
	line ans;
	node *l, *r;
	int siz;
	node(){}
	node(line l) : ans(l), l(nullptr), r(nullptr){ }
};
node sgt[maxn];

int root[maxn], cnt = 0;
struct segtree{
	node *rt;
	int n, siz;
	segtree() : n(maxc * 2), siz(0), rt(nullptr){}
	void insert(node* &k, int l, int r, line cur){
		if(!k){
			k = new node(cur);
			siz++;
			return;
		}
		if(l == r){
			if(k->ans.val(l) > cur.val(l)) k->ans = cur;
			return;
		}
		int m = (l + r) / 2;
		if(k->ans.val(m) > cur.val(m)) swap(k->ans, cur);
		if(cur.m > k->ans.m) insert(k->l, l, m, cur);
		else insert(k->r, m + 1, r, cur);
	}
	void insert(ll m, ll k) { insert(rt, 0, n, line(m, k)); }
	void insert(line l) { insert(rt, 0, n, l);}
	ll qry(node *k, int l, int r, int pos){
		if(!k) return INF;
		if(l == r) return k->ans.val(pos);
		int m = (l + r) / 2;
		return min(k->ans.val(pos), pos <= m ? qry(k->l, l, m, pos) : qry(k->r, m + 1, r, pos));
	}
	ll qry(int pos) { return qry(rt, 0, n, pos); }
};