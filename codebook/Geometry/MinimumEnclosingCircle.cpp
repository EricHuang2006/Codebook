pt circle(pt a, pt b, pt c){
	pt m1 = (a + b) / 2, m2 = (a + c) / 2, d1 = (b - a).rot().norm(), d2 = (c - a).norm();
	double tar = dot(m2, d2) - dot(m1, d2);
	double k = tar / dot(d1, d2);
	return m1 + d1 * k;
}

pair<pt, double> min_enclosing(vector<pt> &a) {
    random_shuffle(a.begin(), a.end());
	pt c = {0, 0};
	double r2 = 0;
	for(int i = 0; i < n; i++){
		if((a[i] - c).len2() <= r2) continue;
		c = a[i], r2 = 0;
		for(int j = 0; j < i; j++){
			if((a[j] - c).len2() <= r2) continue;
			c = (a[i] + a[j]) / 2, r2 = (a[i] - c).len2();
			for(int k = 0; k < j; k++){
				if((a[k] - c).len2() <= r2) continue;
				c = circle(a[i], a[j], a[k]), r2 = (a[k] - c).len2();
			}
		}
	}
  return make_pair(c, sqrt(r2));
}