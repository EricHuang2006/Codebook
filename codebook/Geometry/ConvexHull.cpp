vector<pt> ConvexHull(vector<pt> a) {
  int n = a.size();
  sort(a.begin(), a.end());
  vector <Pt> ans = {a[0]};
  for (int t : {0, 1}) {
    int m = ans.size();
    for (int i = 1; i < n; ++i) {
      while (ans.size() > m && ori(ans[ans.size() - 2],
        ans.back(), pt[i]) <= 0) ans.pop_back();
      ans.pb(pt[i]);
    }
    reverse(all(pt));
  }
  if (ans.size() > 1) ans.pop_back();
  return ans;
}