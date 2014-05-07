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
typedef pair<int,ll> Pair;
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

const int maxn=10000+10;
const ll inf=100000000000000LL;
int n, m, Q, r, Ecnt=0;
ll dist[maxn], cl[maxn], len[maxn], d[maxn];
int s[maxn], p[maxn][14], c[maxn], dep[maxn];
bool v[maxn], InStack[maxn];
deque<Pair> q;
struct Edge {
	int y; ll c;
	Edge *next;
	Edge (int _y,ll _c, Edge *_next) : y(_y), c(_c), next(_next) {}
}*h[maxn];

void Add_Edge(int x,int y,ll c) {
	h[x]=new Edge(y, c, h[x]);
}

void spfa(int x) {
	q.clear();
	rep(i,n) dist[i]=inf;
	dist[x]=0;q.push_back(mp(x, 0));
	for (;;) {
		while (!q.empty() && dist[q.front().first]!=q.front().second) q.pop_front();
		if (q.empty()) break;
		int x=q.front().first;q.pop_front();
		ForE(e,x) {
			int y=e->y;
			if (dist[y] > dist[x]+e->c || (dist[y] == dist[x]+e->c && dep[y] > dep[x]+1)) {
				dist[y] = dist[x]+e->c;
				if (!q.empty() || dist[y] < q.front().second) q.push_front(mp(y, dist[y]));
				else q.push_back(mp(y, dist[y]));
			}
		}
	}
}

void circle(int y) {
	ForD(i,r,0) {
		int x=s[i];
		cl[m]+=len[i];
		if (x==y) break;
		c[x]=m;
		d[x]=(i==r)?(len[i]):(d[s[i+1]]+len[i]);
		Add_Edge(y, s[i], dist[s[i]] - dist[y]);
	}
	++m;
}

void dfs(int x,int fa) {
	v[x]=1;s[++r]=x, InStack[x]=1;
	ForE(e,x) {
		int y=e->y;
		if (y==fa) continue;
		len[r]=e->c;
		if (!v[y]) dfs(y, x);
		else {
			if (!InStack[y]) continue;
			circle(y);
		}
	}
	InStack[x]=0, --r;
}

void prework() {
	For(i,1,13) rep(u,n)
		if (p[u][i-1]!=-1 && p[p[u][i-1]][i-1]!=-1) 
			p[u][i]=p[p[u][i-1]][i-1];
		
}

int lca(int u,int v) {
	if (dep[u]<dep[v]) swap(u, v);
	if (dep[u]!=dep[v]) repD(i,20) if ((1<<i)&(dep[u]-dep[v])) u=p[u][i];
	if (u!=v) {
		repD(i,14) if (p[u][i]!=-1 && p[u][i]!=p[v][i]) u=p[u][i], v=p[v][i];
		u=p[u][0];
	}
	return u;
}
int locate(int u,int d) {
	repD(i,14) if ((1<<i)&d) u=p[u][i];	
	return u;
}	

void bfs(int x) {
	queue<int> q;
	dep[x]=0;
	for (q.push(x); !q.empty(); q.pop()) {
		int x=q.front();
		ForE(e,x) if (dist[x]+e->c==dist[e->y] && dep[e->y]<0) 
			q.push(e->y), dep[e->y]=dep[x]+1, p[e->y][0]=x;
	}
}

int main() {
	setIO("test");
	
	n=gi, m=gi, Q=gi;
	rep(i,m) {
		int a=gi-1, b=gi-1;ll c=gi;
		Add_Edge(a, b, c), Add_Edge(b, a, c);
	}
	
	rep(i,n) rep(j,14) p[i][j]=-1;
	spfa(0);
	
	s[0]=-1, r=-1, m=0;
	rep(i,n) dep[i]=c[i]=-1;
	dfs(0, -1);	
	bfs(0);

	prework();	
	
	rep(i,Q) {
		int u=gi-1, v=gi-1, f=lca(u, v);
		int tu=(u!=f)?locate(u,dep[u]-dep[f]-1):-1;
		int tv=(v!=f)?locate(v,dep[v]-dep[f]-1):-1;
		
		ll ans;
		if (u!=f && v!=f && c[tu]==c[tv] && c[tu]!=-1) ans=dist[u]-dist[tu] + dist[v]-dist[tv] + min(abs(d[tu]-d[tv]), cl[c[tu]]-abs(d[tu]-d[tv])); 
		else ans=dist[u]+dist[v]-(dist[f]<<1);
		
		printf("%lld\n", ans);
	}
	
	return 0;   
}
