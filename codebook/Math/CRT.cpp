ll CRT(vector<ll> p, vector<ll> a){
	ll n = p.size(), prod = 1, ret = 0;
	for(int i = 0; i < n; i++) prod *= p[i];
	for(int i = 0; i < n; i++){
		ll m = (prod / p[i]);
		ll x, y;
		extgcd(m, p[i], x, y);
		ret = ((ret + a[i] * m * x) % prod + prod) % prod;
	}
	return ret;
}