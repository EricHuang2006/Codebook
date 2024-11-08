vector<int> manacher(string s){
    int n = 2 * s.size() + 1;
    string ss(n, '#');
    for(int i = 0; i < n / 2; i++) ss[i * 2 + 1] = s[i];
    swap(s, ss);
    vector<int> f(n);
    int m = 0, len = 0;
    for(int i = 0; i < n; i++){
        f[i] = max(0LL, min(f[m + m - i], m + len - i));
        while(i + f[i] < n && i - f[i] >= 0 && s[i + f[i]] == s[i - f[i]]){
            m = i, len = f[i], f[i]++;
        }
    }
    return f;
}
