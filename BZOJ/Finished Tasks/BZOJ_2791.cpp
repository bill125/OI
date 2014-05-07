#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstdlib>
 
using namespace std;
 
typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = h[a];i != -1;i = E[i].next)
#define ForV(i,a) for (__typeof (a.begin()) i = a.begin();i != a.end();++i) 
#define fill(a,b) memset(a,b,sizeof(a))
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define pb push_back
#define gi gI()

const int inf = ~0U>>1,maxn = 500000+10,maxe = 1000000+10;
int n,m,tE = -1,Index = 0;
int _a[maxn],_b[maxn],h[maxn],to[maxn],d[maxn],cnt[maxn],T[maxn],c[maxn],ans[maxn],ansx[maxn],ansy[maxn];
bool v[maxn];
struct Edge {
	int to,next;
}E[maxe];

void setIO(string name) {
    #ifndef ONLINE_JUDGE
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
    #endif
}

int gI() {
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	int p = 0,flag = 1;
	if (c == '-') flag = -1,c = getchar();
	while (c >= '0' && c <= '9') p = p*10 + c-'0',c = getchar();
	return p*flag;
}

void debug(int *a,int n) {rep(i,n) printf("%d ", a[i]);puts("");}
void debug(ll *a,int n) {rep(i,n) printf("%lld ", a[i]);puts("");}

namespace A {
	int n;
	int f[maxn];
	
	void init(int _n) {
		n = _n;
		rep(i,n) f[i] = i;
	}
	
	int find(int x) {
		if (f[x] != x) f[x] = find(f[x]);
		return f[x];
	}
	
	void merge(int x,int y) {
		x = find(x),y = find(y);
		if (x == y) return;
		f[y] = x;
	}
}

namespace B {
	int n;
	int f[maxn];
	
	void init(int _n) {
		n = _n;
		rep(i,n) f[i] = i;
	}
	
	int find(int x) {
		if (f[x] != x) f[x] = find(f[x]);
		return f[x];
	}
	
	void merge(int x,int y) {
		x = find(x),y = find(y);
		if (x == y) return;
		f[y] = x;
	}
}

void addedge(int x,int y) {
	++tE;
	E[tE].to = y,E[tE].next = h[x],h[x] = tE;
}

void getd(int x) {
	ForE(i,x) {
		d[E[i].to] = d[x] + 1;
		getd(E[i].to);
	}
}

void Clean(int x) {
	v[x] = 1;T[x] = Index;
	if (v[to[x]]) return ;
	d[to[x]] = d[x] + 1;
	cnt[to[x]] = cnt[x] + 1;
	Clean(to[x]);
	cnt[x] = cnt[to[x]];
}

namespace C {
	int n;
	int tE = -1,tT = -1;
	int h[maxn];
	bool v[maxn];
	struct Edge {
		int to,next;
	}E[maxe];
	struct Tag {
		int to,id;
	}t;
	vector<Tag> Q[maxn]; 
	
	void init(int _n) {
		n = _n;
		rep(i,n) h[i] = -1;
		fill(v,0);
	}
	
	void Add_Edge(int a,int b) {
		++tE;
		E[tE].to = b,E[tE].next = h[a],h[a] = tE;
	}
	
	void Add_Tag(int i,int a,int b) {
		t.to = b,t.id = i,Q[a].pb(t);
		t.to = a,t.id = i,Q[b].pb(t);
	}
	
	void DFS(int x,int ans[]) {
		v[x] = 1;
		rep(i,Q[x].size()) {
			t = Q[x][i];
			int f = B::find(t.to);
			if (v[f]) ans[t.id] = f;
		}
		ForE(i,x) {
			int j = E[i].to;
			if (v[j]) continue;
			DFS(j,ans);
			B::merge(x,j);
		}
	}
	
	void Run(int ans[]) {
		DFS(0,ans);
	}
}

void Del() {
	int q[maxn];
	int r = 0;
	fill(v,0);
	rep(i,n) if (!d[i]) {
		v[q[r++] = i] = 1;
		A::merge(to[i],i);
		C::Add_Edge(to[i],i);
		addedge(to[i],i);
	}
	rep(i,r) {
		int x = q[i];
		A::merge(to[x],x);
		C::Add_Edge(to[x],x);
		addedge(to[x],x);
		if (!--d[to[x]]) {
			v[q[r++] = to[x]] = 1;
		}
	}
	fill(d,0);
	rep(i,n) if (!v[i]) {
		cnt[i] = 1;
		Clean(i),++Index;
	}
}

int main() {
	setIO("test"); 
	
	n = gi,m = gi;
	fill(d,0);
	rep(i,n) {
		to[i] = gi-1;
		++d[to[i]];
	}
	A::init(n);B::init(n);C::init(n);
	
	rep(i,n) h[i] = -1;
	Del();
	
	rep(i,n) c[i] = A::find(i);
	
	rep(i,n) 
		if (c[i] == i) 
			getd(i);
	
	rep(i,m) {
		int a = gi-1,b = gi-1;
		if (T[c[a]] != T[c[b]]) 
			ans[i] = ansx[i] = ansy[i] = -1;
		else 
			if (c[a] == c[b]) {
				C::Add_Tag(i,a,b);
				_a[i] = a,_b[i] = b;
			}
			else {
				ans[i] = -1;
				int ta = d[a] - d[c[a]];
				int tb = d[b] - d[c[b]];
				int t1,t2;
				a = c[a],b = c[b];
				if (d[a] > d[b]) {
					t1 = d[b] - d[a] + cnt[a];
					t2 = d[a] - d[b];
				}
				else {
					t1 = d[b] - d[a];
					t2 = d[a] - d[b] + cnt[a];
				}
				int nx,ny;
				nx = ta + t1,ny = tb;
				ansx[i] = nx,ansy[i] = ny;
				nx = ta,ny = tb + t2;
				if (max(nx,ny) < max(ansx[i],ansy[i])) 
					ansx[i] = nx,ansy[i] = ny;
				else if (max(nx,ny) == max(ansx[i],ansy[i]) && min(nx,ny) < min(ansx[i],ansy[i])) 
					ansx[i] = nx,ansy[i] = ny;
				else if (min(nx,ny) == min(ansx[i],ansy[i]) && nx >= ny) 
					ansx[i] = nx,ansy[i] = ny;
			}
	}
	
	rep(i,n) if (c[i] == i) C::DFS(i,ans);
	
	rep(i,m) 
		if (ans[i] != -1) {
			ansx[i] = d[_a[i]] - d[ans[i]];
			ansy[i] = d[_b[i]] - d[ans[i]];
		}
		
	rep(i,m) printf("%d %d\n", ansx[i],ansy[i]);
	
	return 0;
}
