ll f(ll t, ll c, ll n){
	return ((u128)t * t + c) % n;
}
ll Pollard_Rho(ll x){
	ll t = 0;
	ll c = rand() % (x - 1) + 1;
	ll s = t;
	ll val = 1;
	for(int goal = 1;; goal <<= 1, s = t, val = 1){
		for(int step = 1; step <= goal; step++){
			t = f(t, c, x);
			val = (u128)val * abs(t - s) % x;
			if(!val) return x;
			if(step % 127 == 0){
				ll d = __gcd(val, x);
				if(d > 1) return d;
			}
		}
		ll d = __gcd(val, x);
		if(d > 1) return d;
	}
    return x;
}
void fac(vector<ll> &ans, ll x){
    if(x <= 1) return;
    if(MillerRabin(x)) ans.pb(x);
    else{
        ll t = Pollard_Rho(x);
        fac(ans, x / t);
        fac(ans, t);
    }
}

