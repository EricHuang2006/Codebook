vector<pll> adj[maxn];
ll dist[20][maxn]; // distance to kth-layer-parent
int sz[maxn], del[maxn], par[maxn], cdep[maxn];
ll cnt[maxn], sum[maxn], re[maxn]; // re: subtree->par
int n, q;

void dfssz(int pos, int prev){
    sz[pos] = 1;
    for(auto [x, w] : adj[pos]){
        if(del[x] || x == prev) continue;
        dfssz(x, pos);
        sz[pos] += sz[x];
    }
}
int get_centroid(int pos, int prev, int siz){
    for(auto [x, w] : adj[pos]){
        if(!del[x] && x != prev && sz[x] > siz / 2) return get_centroid(x, pos, siz);
    }
    return pos;
}
void get_dist(int pos, int prev, int layer){
    for(auto [x, w] : adj[pos]){
        if(del[x] || x == prev) continue;
        dist[layer][x] = dist[layer][pos] + w;
        get_dist(x, pos, layer);
    }
}
void cd(int pos, int layer = 1, int p = 0){
    dfssz(pos, -1);
    int cen = get_centroid(pos, -1, sz[pos]);
    del[cen] = 1;
    dist[layer][cen] = 0;
    cdep[cen] = layer;
    par[cen] = p;
    get_dist(cen, -1, layer);
    for(auto [x, w] : adj[cen]){
        if(!del[x]){
            cd(x, layer + 1, cen);
        }
    }
}
void upd(int p){
    for(int x = p, d = cdep[x]; d; x = par[x], d--){
        sum[x] += dist[d][p];
        re[x] += dist[d - 1][p];
        cnt[x] ++;
    }
}
ll qry(int p){
    ll pre = 0, ans = 0;
    for(int x = p, d = cdep[x]; d; x = par[x], d--){
        ans += sum[x] - re[x] + (cnt[x] - pre) * dist[d][p];
        pre = cnt[x];
    }
    return ans;
}