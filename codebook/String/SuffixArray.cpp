struct SuffixArray{
    int ch[2][maxn], sa[maxn], cnt[maxn], n;
    string s;
    void init(string _s){
        s = _s, n = s.size();
        Get_SA();
        Get_LCP();
    }
    void Get_SA(){
        int *x = ch[0], *y = ch[1], m = 256;
        for(int i = 0; i < m; i++) cnt[i] = 0;
        for(int i = 0; i < n; i++) cnt[x[i] = s[i]]++;
        for(int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for(int i = 0; i < n; i++) sa[--cnt[x[i]]] = i;
        for(int k = 1;; k <<= 1){
            for(int i = 0; i < m; i++) cnt[i] = 0;
            for(int i = 0; i < n; i++) cnt[x[i]]++;
            for(int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
            int p = 0;
            for(int i = n - k; i < n; i++) y[p++] = i;
            for(int i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
            for(int i = n - 1; i >= 0; i--) sa[--cnt[x[y[i]]]] = y[i];
            y[sa[0]] = p = 0;
            for(int i = 1; i < n; i++){
                int a = sa[i], b = sa[i - 1];
                if(a + k < n && b + k < n && x[a] == x[b] && x[a + k] == x[b + k]);
                else p++;
                y[a] = p;
            }
            if(p == n - 1) break;
            swap(x, y);
            m = p + 1;
        }
    }
    int rnk[maxn], lcp[maxn];
    void Get_LCP(){
        for(int i = 0; i < n; i++) rnk[sa[i]] = i;
        int val = 0;
        for(int i = 0; i < n; i++){
            if(val) val--;
            if(!rnk[i]){
                lcp[0] = val = 0;
                continue;
            }
            int b = sa[rnk[i] - 1];
            while(b + val < n && i + val < n && s[b + val] == s[i + val]) val++;
            lcp[rnk[i]] = val;
        }
    }
} sa;
