const int N = 998244353, g = 3;

void NTT(vector<ll> &a, bool invert = 0){ // interative version
	int n = a.size();
	int lg_n = __lg(n);
	for(int i = 1, j = 0; i < n; i++){ 
		int bit = n >> 1;
		for(; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if(i < j) swap(a[i], a[j]);
	}
	for(int len = 2; len <= n; len <<= 1){
		ll wn = fpow(g, (N - 1) / len); 
		if(invert) wn = inv(wn); 	
		for(int i = 0; i < n; i += len){
			ll w = 1;
			for(int j = 0; j < len / 2; j++){
				ll u = a[i + j], v = a[i + j + len / 2] * w % N;
				a[i + j] = (u + v) % N;
				a[i + j + len / 2] = (u - v + N) % N;
				(w *= wn) %= N;
			}
		}
	}
	ll n_1 = inv(n);
	if(invert) for(auto &x : a) (x *= n_1) %= N;
}