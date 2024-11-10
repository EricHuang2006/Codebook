void linearsieve(){
	phi[1] = 1;
	for(int i = 2; i < maxn; i++){
		if(!lp[i]) pr.pb(i), lp[i] = i, phi[i] = i - 1;
		for(auto x : pr){
			if(i * x >= maxn) break;
			lp[i * x] = x;
			if(lp[i] == x){
				phi[i * x] = phi[i] * x;
				break;
			}
			phi[i * x] = phi[i] * (x - 1);
		}
	}
	for(int i = 1; i < maxn; i++) sum[i] = (sum[i - 1] + i * phi[i]) % N;
}

int s2(int n){
	static const int inv6 = inv(6);
	n %= N;
	return n * (n + 1) % N * (2 * n + 1) % N * inv6 % N;
}

int G(int n){
	static const int inv2 = inv(2);
	if(n < maxn) return sum[n];
	if(mp_G.count(n)) return mp_G[n];
	int ans = s2(n);
	for(int i = 2, j; i <= n; i = j + 1){
		j = n / (n / i);
		(ans -= (i + j) % N * (j - i + 1) % N * inv2 % N * G(n / i) % N - N) %= N;
	}
	return mp_G[n] = ans;
}

void dfs(int d, int hd, int p){ // dfs 出所有 PN
	(ans += hd * G(n / d)) %= N;
	for(int i = p; i < pr.size(); i++){
		if(d > n / pr[i] / pr[i]) break;
		int c = 2;
		for(int x = d * pr[i] * pr[i]; x <= n; x *= pr[i], c++){
			if(!vis[i][c]){
				int f = fpow(pr[i], c);
				f = f * (f - 1) % N;
				int g = pr[i] * (pr[i] - 1) % N;
				int t = pr[i] * pr[i] % N;
				for(int j = 1; j <= c; j++){
					(f -= g * h[i][c - j] % N - N) %= N;
					(g *= t) %= N;
				}
				h[i][c] = f;
				vis[i][c] = true;
			}
			if(h[i][c]) dfs(x, hd * h[i][c] % N, i + 1);
		}
	}
}

linearsieve();
for(int i = 0; i < pr.size(); i++) h[i][0] = 1;
dfs(1, 1, 0);