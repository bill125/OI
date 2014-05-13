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

const int inf=~0U>>1, maxn = 200+10, maxp = 400+10, maxe=maxp*maxp*2;
const db eps = 1e-6;
int n, m, k;

//db abs(db n) { return (n > 0) ? n : -n; }
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

struct Lich {
	Point u; db r;
	int t;
}A[maxn];
Point B[maxn];
Circle C[maxn];
bool Kill[maxn][maxn];

struct Dinic {
	int n,s,t,delta;
	struct Edge {
		int y,f;
		Edge *r,*next;
		Edge () {}
		Edge (int _y,int _f,Edge *_next) : y(_y), f(_f), next(_next) {} 
	}*h[maxp], *cur[maxp], mem[maxe], *E;
	int d[maxp],q[maxp];
	void init(int _n, int _s,int _t) {
		n=_n, s=_s, t=_t;
		E=mem;
		fill(h,0);
	}
	Edge *makeedge(int x,int y,int f) {
		E->next = h[x], E->y = y, E->f = f;
		return E++;
	}
	void Add_Edge(int x,int y,int f) {
		h[x]=makeedge(x, y, f),h[y]=makeedge(y, x, 0);
		h[x]->r=h[y],h[y]->r=h[x];
	}
	bool Build() {
		fill(d,127);d[s]=0;
		q[0]=s;int r=1;
		rep(i,r) {
			int x=q[i];
			ForE(e,x) if (e->f) {
				int y=e->y;
				if (d[x]+1<d[y]) {
					d[y]=d[x]+1;
					if (y==t) return 1;
					q[r++]=y;
				}
			}
		}
		return 0;
	}
	bool Find(int x,int now_flow) {
		if (x==t) {
			delta=now_flow;
			return 1;
		}
		for (Edge *e=cur[x]; e; e=e->next) if (e->f) {
			cur[x]=e;
			int y=e->y;
			if (d[x]+1==d[y] && Find(y,min(now_flow,e->f))) {
				e->f-=delta,e->r->f+=delta;
				return 1;
			}
		}
		return 0;
	}
	int MaxFlow() {
		int res=0;
		while (Build()) {
			rep(i,n) cur[i]=h[i];
			while (Find(s,inf)) res+=delta;
		}			
		return res;
	}
}D;

bool InSight(Lich u, Point v) {
	bool flag = 1;
	rep(i, k) 
		if (IntersectCS(C[i], Seg(u.u, v))) {
			flag = 0; break;
		}
	return flag;
}

bool check(int Time) {
	int S = 0, T = n + m + 1;
	D.init(n+m+2, S, T);
	rep(i, n) rep(j, m) if (Kill[i][j]) {
		D.Add_Edge(i+1, j+n+1, 1);
	}
	rep(i, n) D.Add_Edge(S, i+1, Time/A[i].t+1);
	rep(i, m) D.Add_Edge(i+n+1, T, 1);
	return D.MaxFlow() == m;
}

int main() {
	setIO("test");
	
	n = gi, m = gi, k = gi;	
	
	rep(i, n) A[i].u.x = gi, A[i].u.y = gi, A[i].r = gi, A[i].t = gi;
	rep(i, m) B[i].x = gi, B[i].y = gi;
	rep(i, k) C[i].u.x = gi, C[i].u.y = gi, C[i].r = gi;
	
	rep(i,n) rep(j,m) {
		Kill[i][j] = InSight(A[i], B[j]) && dis(A[i].u, B[j]) <= A[i].r;
		//if (Kill[i][j]) printf("%d %d\n", i, j);
	}
	
	int l = -1, r = n * 200000;
	if (!check(r)) {puts("-1"); return 0;}
	if (check(0)) {puts("0"); return 0;}
	while (l + 1 < r) {
		int m = l + r >> 1;
		if (check(m)) r = m;
		else l = m;
	}
	
	printf("%d\n", r );
	
	return 0;   
}
