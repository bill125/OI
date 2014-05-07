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

const int inf=~0U>>1, maxn=100000+10, maxm=200000+10, maxe=200000+10;
int n,m;
int x[maxm], y[maxm], t[maxm], p[maxn], d[maxn], ans[maxn], dep[maxn], f[maxn], num[maxm];

bool cmp(int a,int b) {
	return t[a]<t[b];
}

int find(int x) {
    if (x!=p[x]) p[x]=find(p[x]);
    return p[x];
}
 
void merge(int x,int y) {
    p[y]=x;
}
 
void update(int u,int v,int t) {
    int x=u, y=v;
    u=find(u), v=find(v);
    while (u!=v) {
        int tu=find(f[u]), tv=find(f[v]);
        if (u && (!v || dep[tu]>=dep[tv])) {
            ans[u]=min(ans[u], t-d[u]);
            merge(tu, u);
            u=tu;
        }
        else {
            ans[v]=min(ans[v], t-d[v]);
            merge(tv, v);
            v=tv;
        }
    }
}

struct Edge {
	int t,c;
	Edge *next;
	Edge (int _t,int _c, Edge *_next) : t(_t), c(_c), next(_next) {};
}*h[maxn];

struct State {
	int t,x;
	State() {}
	State(int _t,int _x) : t(_t), x(_x) {}
	inline bool operator <(const State& o) {return x < o.x;}  
};

template <class T>
struct Heap {
	int sz;
	T A[maxe];
	Heap(): sz(0) {} 
	void clear() {
		sz = 0;
	}
	T top() {
		return A[1];
	}
	void up(int x) {
		while (x>1) {
			if (A[x>>1]<A[x]) return ;
			swap(A[x],A[x>>1]);
			x>>=1;
		}
	}
	void down(int x) {
		while ((x<<1) <= sz) {
			int y = ((x<<1)+1 <= sz && A[(x<<1)+1] < A[(x<<1)]) ? (x<<1)+1 : (x<<1);
			if (A[x]<A[y]) return ; 
			swap(A[x],A[y]);
			x = y;
		}
	}
	void push(const T &t) {
		A[++sz] = t;
		up(sz);
	}
	void pop() {
		swap(A[1],A[sz--]);
		down(1);
	}
};
Heap<State> Q;

void Add_Edge(int s,int t,int c) {
	h[s]=new Edge(t, c, h[s]);
}

void Dijkstra(const int &x,int d[]) {
	rep(i,n) d[i] = inf;
	d[x] = 0, dep[x] = 0;
	Q.push(State(x,0));
	rep(i,n) {
		State now;
		while (true) {
			now = Q.top();
			Q.pop();
			if (d[now.t] == now.x) break;
		}
		ForE(e,now.t)
			if (d[now.t] + e->c < d[e->t]) {
				dep[e->t]=d[now.t] + 1;
				f[e->t] = now.t;
				d[e->t] = d[now.t] + e->c;
				Q.push(State(e->t,d[e->t]));
			} 	
	}
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,m) {
		x[i]=gi-1, y[i]=gi-1, t[i]=gi;
		Add_Edge(x[i], y[i], t[i]);
		Add_Edge(y[i], x[i], t[i]);
	}
	
	rep(i,n) d[i]=inf;
	Dijkstra(0, d);
	rep(i,m) t[i]+=d[x[i]]+d[y[i]], num[i]=i;

	sort(num, num+m, cmp);
	rep(i,n) p[i]=i;
	
	rep(i,n) ans[i]=inf;
	rep(_i,m) {
		int i=num[_i];
		if (x[i]==f[y[i]] || y[i]==f[x[i]]) continue;
		update(x[i], y[i], t[i]);
	}
	
	For(i,1,n-1) printf("%d\n", (ans[i]==inf)?-1:ans[i]);
	
	return 0;
}
