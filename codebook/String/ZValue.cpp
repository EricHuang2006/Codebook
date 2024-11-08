vector<int> z(string s){
    vector<int> z(s.size());
    int x = 0, y = 0;
    for(int i = 1; i < s.size(); i++){
        z[i] = max(0LL, min(z[i - x], y - i));
        while(i + z[i] < s.size() && s[i + z[i]] == s[z[i]]){
            x = i, y = i + z[i], z[i]++;
        }
    }
    return z;
}