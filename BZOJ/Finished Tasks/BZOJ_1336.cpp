// Author: bill125
// ntr jcpwfloi
// orz LXLWDGY WJMZBMR dilutedream sevenkplus 
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <bitset>
#include <cmath>

using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> Pair;
#define rep(i,n) for (int i=0; i<n; ++i)
#define repD(i,n) for (int i=n-1; i>=0; --i)
#define For(i,a,b) for (int i=a; i<=b; ++i)
#define ForD(i,a,b) for (int i=a; i>=b; --i)
#define ForE(i,a) for (Edge* i=h[a]; i; i=i->next)
#define forv(i,a) for (unsigned int i=0, ___t=a.size(); i<___t; ++i)
#define ForV(i,a) for (__typeof(a.begin()) i = a.begin();i != a.end();++i)
#define fill(a,b) memset(a,b,sizeof(a))
#define lowbit(a) ((a) & (-(a)))
#define sqr(a) ((a)*(a))
#define pb push_back
#define mp make_pair
#define gi gI()
#define cut puts("===================")
 
void setIO(string NAME) {
	#ifndef ONLINE_JUDGE
	string in=NAME+".in", out=NAME+".out";freopen(in.c_str(),"r",stdin),freopen(out.c_str(),"w",stdout);
	#endif
}
inline ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxn = 100000+10;
int n;
//db abs(db n) { return (n > 0) ? n : -n; }
const db eps = 1e-8;
struct Point {
	db x, y;
	Point (db _x=0, db _y=0) : x(_x), y(_y) {}
	friend Point operator + (const Point &u, const Point &v) { return Point(u.x + v.x, u.y + v.y); }
	friend Point operator - (const Point &u, const Point &v) { return Point(u.x - v.x, u.y - v.y); }
	friend Point operator / (const Point &u, const db &v) { return Point(u.x / v, u.y / v); }
	friend Point operator * (const Point &u, const db &v) { return Point(u.x * v, u.y * v); }
	void print() { printf("(%.3f, %.3f)\n", x, y); }
	db abs() { return hypot(x, y); }
};
struct Seg { 
	Point A, B; 
	Seg () {}
	Seg (Point _A, Point _B) : A(_A), B(_B) {}
};
struct Circle { Point u; db r; };
db dot(Point u, Point v) { return u.x * v.x + u.y * v.y; }
db det(Point u, Point v) { return u.x * v.y - u.y * v.x; }
typedef Point Vector;
bool OnLine(Point u, Seg v) {
	return abs( det(v.A - u, v.B - u) ) < eps;
}
bool OnSeg(Point u, Seg v) {
	return OnLine(u, v) && (u.x - v.A.x) * (u.x - v.B.x) <= 0 && (u.y - v.A.y) * (u.y - v.B.y) <= 0; 
}
db dis(Point u, Point v) {
	Vector t = v - u;
	return t.abs();
}
db dis(Point u, Seg v) {
	Vector t = v.B - v.A;
	return abs( det(v.A - u, v.B - u) / t.abs() );
}
Point Proj(Point P, Seg v) {
	Vector AP = P - v.A;
	Vector AB = v.B - v.A;
	Vector t = (AB / AB.abs()) * (dot(AP, AB) / AB.abs()); 
	return v.A + t;
}
Point IsP(Circle a,Seg b) {
	Point A = Proj(a.u, b);
	Vector t = b.A - A; 
	db d = dis(a.u, b);
	t = t / t.abs() * sqrt(sqr(a.r) - sqr(d));
	return A + t;
}
Point IsP(Seg u, Seg v) {
	Vector t = u.A - v.A;
	return u.A + (u.B - u.A) * (det(v.B - v.A, t) / det(u.B - u.A, v.B - v.A));
}
bool IntersectCL(Circle a, Seg b) {
	return dis(a.u, b) <= a.r + eps;
}
bool IntersectCS(Circle a, Seg b) {
	if (!IntersectCL(a, b)) return 0;
	Point A = IsP(a, b);
	swap(b.A, b.B);
	Point B = IsP(a, b);
	return OnSeg(A, b) || OnSeg(B, b);
}
Point Circumcenter(Point A,Point B,Point C) {
	if (OnLine(B, Seg(A, C))) {
		if (B.x < A.x) swap(A, B);
		if (C.x < A.x) swap(A, C);
		if (C.x < B.x) swap(B, C);
		return (A + C) / 2;
	}
	Point M1 = (A + B) / 2, M2 = (A + C) / 2;
	Vector V1 = B - A, V2 = C - A;
	swap(V1.x, V1.y), swap(V2.x, V2.y);
	V1.x = -V1.x, V2.x = -V2.x;
	return IsP(Seg(M1, M1 + V1), Seg(M2, M2 + V2));
}

Point P[maxn];

void RandomShuffle() {
	rep(i, n/10) {
		int j = rand() % n;
		int k = rand() % n;
		swap(P[j], P[k]);
	}
}

int main() {
	setIO("test");
	
	n = gi;
	rep(i, n) scanf("%lf %lf", &P[i].x, &P[i].y);
	
	random_shuffle(P, P+n);
	
	Circle c;
	c.u = P[0], c.r = 0;
	For(i, 1, n-1) if (dis(P[i], c.u) > c.r + eps) {
		c.u = P[i], c.r = 0;
		rep(j, i) if (dis(P[j], c.u) > c.r + eps) {
			c.u = (P[i] + P[j]) / 2, c.r = dis(P[i], P[j]) / 2;
			rep(k, j) if (dis(P[k], c.u) > c.r + eps) { 
				c.u = Circumcenter(P[i], P[j], P[k]);
				c.r = max((P[i] - c.u).abs(), (P[j] - c.u).abs());
			}
		}
	}
	
	printf("%.8f\n", c.r);
	printf("%.8f %.8f\n", c.u.x, c.u.y);
	
	return 0;   
}
