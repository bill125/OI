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

const int inf=~0U>>1, maxn=100000+10;
int n,m;
struct Edge {
	int y;
	Edge *next;
	Edge (int _y,Edge *_next) : y(_y), next(_next) {}
}*h[maxn];
int q[maxn], dep[maxn], dp[maxn][3], p[maxn][20], up[maxn][20], down[maxn][20];
bool v[maxn], used[2];

void Add_Edge(int a,int b) { h[a]=new Edge(b, h[a]); }

int lca(int u,int v) {
	if (dep[u] < dep[v]) swap(u, v);
	repD(i,20) if ((1<<i) & (dep[u]-dep[v])) u=p[u][i];
	if (u!=v) {
		repD(i,20) if (p[u][i]!=p[v][i]) u=p[u][i], v=p[v][i];
		u=p[u][0];
	}
	return u;
}

int calcup(int u,int f) {
	int res=0, m=0;
	repD(i,20) if ((1<<i) & (dep[u] - dep[f])) {
		res=max(res, up[u][i] + m);
		m += 1 << i; u = p[u][i];
	}
	return res;
}

int calcdown(int u,int f) {
	int res=0;
	repD(i,20) if ((1<<i) & (dep[u] - dep[f] - 1)) {
		res=max(res, down[u][i] + dep[p[u][i]] - dep[f] - 1);
		u = p[u][i];
	}
	return res;
}

int getp(int u,int len) { 
	repD(i,20) if ((1<<i) & len) u=p[u][i]; return u; 
}

int main() {
	setIO("test");
	
	int n=gi, r=1;
	rep(i,n-1) {
		int a=gi-1, b=gi-1;
		Add_Edge(a, b), Add_Edge(b, a);
	}
	fill(p, -1), fill(up, -1), fill(down, -1);
	q[0]=0, v[0]=1;
	rep(i,r) {
		int x=q[i];
		ForE(e,x) { 
			int y=e->y;
			if (!v[y]) q[r++]=y, v[y]=1, dep[y]=dep[x]+1, p[y][0]=x;
		}
	}
	
	fill(dp, -1);
	repD(i,r) {
		int x=q[i];dp[x][0]=0;
		ForE(e,x) { int y=e->y;
			if (y!=p[x][0]) { 
				rep(j,3) if (dp[y][0]!=-1 && dp[y][0]+1 > dp[x][j]) {
					ForD(k,2,j+1) dp[x][k]=dp[x][k-1];
					dp[x][j]=dp[y][0]+1;
					break;
				}
			}
		}
		ForE(e,x) { int y=e->y;
			if (y!=p[x][0]) {
				up[y][0]=(dp[x][0]==dp[y][0]+1)?(dp[x][1]+1):(dp[x][0]+1);
				down[y][0]=(dp[x][0]==dp[y][0]+1)?dp[x][1]:dp[x][0];
			}
		}
	}
	
	For(k,1,19) rep(i,n) 
		if (p[i][k-1]!=-1 && p[p[i][k-1]][k-1]!=-1) {
			p[i][k]=p[p[i][k-1]][k-1];
			up[i][k]=max(up[i][k-1], up[p[i][k-1]][k-1]+(1<<k-1));
			down[i][k]=max(down[i][k-1]+(1<<k-1), down[p[i][k-1]][k-1]);
		}
	
	m=gi;
	rep(i,m) {
		int u=gi-1, v=gi-1;
		if (u==v) { printf("%d\n", max(dp[u][0], calcup(u, 0))); continue; }
		if (dep[u] > dep[v]) swap(u, v);
		int f=lca(u, v), len=(dep[u] + dep[v] - (dep[f] << 1) - 1) >> 1;
		int t=getp(v, len), tu=(u!=f)?getp(u, dep[u] - dep[f] - 1):-1, tv=getp(v, dep[v] - dep[f] - 1);
		
		int ans=(u!=f)?max(dp[u][0], dp[v][0]):dp[v][0];
		ans=max(ans, calcup(v, t));
		if (p[t][0] != f) ans=max(ans, calcdown(t, f) + dep[u] - dep[f] + 1);
		ans=max(ans, calcup(u, getp(u, dep[u] - dep[f] - 1)));
		if (u==f) ans=max(ans, (dp[tv][0]+1 == dp[f][0]) ? dp[f][1] : dp[f][0]);
		else {
			int k;used[0]=used[1]=0;
			for (k=0; ;++k) {
				bool flag=1;
				if (flag && !used[0] && dp[tu][0]+1==dp[f][k]) used[0]=1, flag=0;
				if (flag && !used[1] && dp[tv][0]+1==dp[f][k]) used[1]=1, flag=0;
				if (flag) break;
			}
			if (dp[f][k]!=-1) ans=max(ans, dp[f][k] + dep[u] - dep[f]);
		}
		ans=max(ans, calcup(f, 0) + dep[u] - dep[f]);
		printf("%d\n", ans);
	}
	
	return 0;
}
