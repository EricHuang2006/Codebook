vector<string> duval(string s){
	int n = s.length(), i = 0;
    vector<string> fac;
	while(i < n){
		int j = i + 1, k = i; // i <= k < j
		while(j < n && s[k] <= s[j]){
			if(s[k] < s[j]) k = i;
			else k++;
			j++;
		}
		while(i <= k){
			fac.pb(s.substr(i, j - k));
			i += j - k;
		}
	}
	return fac;
}