struct pt{
    double x, y;
    pt(){}
    pt(double _x, double _y) : x(_x), y(_y){}
};
pt operator + (pt a, pt b)
{ return pt(a.x + b.x, a.y + b.y); }
pt operator - (pt a, pt b)
{ return pt(a.x - b.x, a.y - b.y); }
pt operator * (pt a, double p)
{ return pt(a.x * p, a.y * p); }
pt operator / (pt a, double p)
{ return pt(a.x / p, a.y / p); }
bool operator < (const pt &a, const pt &b) 
{ return a.x < b.x || (a.x == b.x && a.y < b.y); }
bool operator == (const pt &a, const pt &b) 
{ return a.x == b.x && a.y == b.y; }
double dot(pt a, pt b)
{ return a.x * b.x + a.y * b.y; }
double cross(pt a, pt b)
{ return a.x * b.y - a.y * b.x; }
double len(pt a)
{ return sqrt(dot(a, a)); }
double angle(pt a, pt b)
{ return acos(dot(a, b) / len(a) / len(b)); }
double area2(pt a, pt b, pt c)
{ return cross(b - a, c - a); }

const double eps = 1e-9;
int dcmp(double x){
	if(fabs(x) < eps) return 0; 
	return x < 0? -1 : 1;
}

inline int ori(pt a, pt b, pt c){
	double area = cross(b - a, c - a);
	if(area > -eps && area < eps) return 0;
	return area > 0 ? 1 : -1;
}

inline int btw(pt a, pt b, pt c){ // [a, c, b]
	if(fabs(cross(b - a, c - a)) > eps) return false;
	if(dot(b - a, c - a) > -eps && len(c - a) <= len(b - a)) return true;
	return false;
}

bool intersect(pt a, pt b, pt c, pt d){
	if(a == c || a == d || b == c || b == d) return true;
	int a123 = ori(a, b, c), a124 = ori(a, b, d), a341 = ori(c, d, a), a342 = ori(c, d, b);
	if(a123 == 0 && a124 == 0){
		if(btw(a, b, c) || btw(a, b, d) || btw(c, d, a) || btw(c, d, b)) return true;
		else return false;
	}
	else if(a123 * a124 <= 0 && a341 * a342 <= 0) return true;
	return false;
}

istream &operator>>(istream &s, pt &a){
	s >> a.x >> a.y;
	return s;
}