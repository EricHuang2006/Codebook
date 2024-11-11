struct MaximumClique{
    typedef bitset<maxn> bst;
    bst adj[maxn], empt;
    int p[maxn], n, ans;
    void init(int _n){
        n = _n;
        for(int i = 0; i < n; i++) adj[i].reset();
    }
    void BronKerbosch(bst R, bst P, bst X){
        if(P == empt && X == empt){
            ans = max(ans, (int)R.count());
            return;
        }
        bst tmp = P | X;
        if((R | P | X).count() <= ans) return;
        int u;
        for(int i = 0; i < n; i++){
            if(tmp[u = p[i]]) break;
        }
        bst lim = P & ~adj[u];
        for(int i = 0; i < n; i++){
            int v = p[i];
            if(lim[v]){
                R[v] = 1;
                BronKerbosch(R, P & adj[v], X & adj[v]);
                R[v] = 0, P[v] = 0, X[v] = 1;
            }
        }
    }
    void add_edge(int a, int b){
        adj[a][b] = adj[b][a] = 1;
    }
    int solve(){
        bst R, P, X;
        ans = 0, P.flip();
        iota(p, p + n, 0);
        random_shuffle(p, p + n), BronKerbosch(R, P, X);
        return ans;
    }
};