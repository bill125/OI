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

const int inf=~0U>>1, maxn=500+10, maxm=500+10;
int n, m, allcv, tag, Index, Td=0;
struct Edge {
	int y;
	Edge *next;
}*h[maxn], mem[maxm], *e;
int dfn[maxn], low[maxn], cv[maxn], c[maxn];
ll ans1, ans2, cntcv, cntv;
bool vis[maxn];

Edge *makeedge(int a,int b) {
	e->y=b, e->next=h[a];
	return e++;
}

void Add_Edge(int a,int b) {
	h[a]=makeedge(a, b);
}

void tarjan(int u) {
	dfn[u]=low[u]=Index++;vis[u]=1;
	ForE(e,u) {
		int v=e->y;
		if (!vis[v]) {
			tarjan(v), low[u]=min(low[u], low[v]);
			if (low[v] >= dfn[u]) ++cv[u];
		}
		else low[u]=min(low[u], dfn[v]);
	}
}

void dfs(int u) {
	vis[u]=1;++cntv;
	ForE(e,u) {
		int v=e->y;
		if (vis[v]) continue;
		if (!cv[v]) dfs(v);
		else if (c[v]!=tag) c[v]=tag, ++cntcv;
	}
}

int main() {
	setIO("test");
	
	while ((m=gi)) {
		fill(h, 0); fill(dfn, -1); fill(cv, 0);
		e=mem, Index=allcv=tag=n=0;
		rep(i, m) {
			int a=gi-1, b=gi-1;
			n=max(n, a), n=max(n, b);
			Add_Edge(a, b), Add_Edge(b, a);
		}
		++n;
		fill(vis, 0);
		rep(i,n) if (!vis[i]) tarjan(i), --cv[i];
		ans1=0, ans2=1;
		
		fill(vis, 0), fill(c, 0);
		rep(i,n) if (!vis[i] && !cv[i]) {
			cntcv=cntv=0, ++tag;
			dfs(i);
			if (cntcv==1) ++ans1, ans2*=cntv;
		}
		if (tag==1) ans1=2, ans2=n*(n-1)/2;
		printf("Case %d: %I64d %I64d\n", ++Td, ans1, ans2);
	}
	
	return 0;   
}
