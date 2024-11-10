void reorder(vector<pt> &a){
    int pos = 0;
    for(int j = 1; j < a.size(); j++){
        if(a[j].x < a[pos].x || (a[j].x == a[pos].x && a[j].y < a[pos].y)) pos = j;
    }
    rotate(a.begin(), a.begin() + pos, a.end());
}

vector<pt> minkowski(vector<pt> a, vector<pt> b){
    // for(int i = 0; i < b.size(); i++) b[i] = {-b[i].x, -b[i].y}; 最短距離：把 Q 鏡像，找凸包到 (0, 0) 的最短距離
    reorder(a), reorder(b);
    a.pb(a[0]), a.pb(a[1]);
    b.pb(b[0]), b.pb(b[1]);
    vector<pt> res;
    int i = 0, j = 0;
    while(i < a.size() - 2 || j < b.size() - 2){
        res.pb(a[i] + b[j]);
        int c = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
        if(c >= 0 && i < a.size() - 2) i++;
        if(c <= 0 && j < b.size() - 2) j++;
    }
    return res;
}