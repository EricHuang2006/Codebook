using cd = complex<double>;
const double PI = acos(-1);

void FFT(vector<cd> &a, bool invert = 0){ // interative version
	int n = a.size();
	int lg_n = __lg(n);
	for(int i = 1, j = 0; i < n; i++){ //bit-reversal permutation
		int bit = n >> 1;
		for(; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if(i < j) swap(a[i], a[j]);
	}
	for(int len = 2; len <= n; len <<= 1){
		double ang = 2 * PI / len * (invert? -1 : 1);
		cd wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len){
			cd w(1);
			for(int j = 0; j < len / 2; j++){
				cd u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if(invert) for(auto &x : a) x /= n;
}