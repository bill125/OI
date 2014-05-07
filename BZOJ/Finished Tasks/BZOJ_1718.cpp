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

const int inf=~0U>>1, maxn=10000+10;
int n,m,Index=0;
int dfn[maxn], low[maxn], v[maxn], deg[maxn], tag[maxn];
map<int, int> f[maxn];
struct Edge {
	int y;
	Edge *next, *r;
	bool bridge;
	Edge (int _y, Edge* _next) : y(_y), next(_next) {bridge=0;}
}*h[maxn];

Edge *makeedge(int x,int y) {
	return new Edge(y, h[x]);
}

void Add_Edge(int x,int y) {
	Edge *e1=h[x]=makeedge(x, y), *e2=h[y]=makeedge(y, x);
	e1->r=e2, e2->r=e1;
}

void dfs(int x,int fa) {
	v[x]=1;
	dfn[x]=low[x]=++Index;
	ForE(e,x) {
		int y=e->y;
		if (y!=fa && v[y]==1) low[x]=min(low[x], dfn[y]);
		if (!v[y]) {
			dfs(y, x);
			low[x]=min(low[x], low[y]);
			if (dfn[x]<low[y]) e->bridge=e->r->bridge=1;
		}
	}
	v[x]=2;
}

void color(int x,int c) {
	tag[x]=c;
	ForE(e,x) if (!e->bridge && tag[e->y]<0) color(e->y, c);
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,m) {
		int a=gi-1, b=gi-1;
		if (f[a].count(b)) continue;
		f[a][b]=f[b][a]=1;
		Add_Edge(a,b);
	}
	
	dfs(0, -1);
	fill(tag, -1);
	int cnt=0;
	
	rep(i,n) if (tag[i]<0) color(i, cnt++);
	rep(i,n) ForE(e,i) if (e->bridge) ++deg[tag[e->y]];
	
	int ans=0;
	rep(i,cnt) ans+=deg[i]==1;
	
	printf("%d\n", (ans+1)/2);
	
	return 0;   
}
