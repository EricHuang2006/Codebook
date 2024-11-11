vector<int> KMP(string s){
    vector<int> f(s.size());
    for(int i = 1; i < s.size(); i++){
        f[i] = f[i] - 1;
        while(f[i] && s[i] != s[f[i]]) f[i] = f[f[i] - 1];
        if(s[f[i]] == s[i]) f[i]++;
    }
    return f;
}
