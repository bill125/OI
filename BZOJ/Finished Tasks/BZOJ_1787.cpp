// Author: bill125
// ntr czr
// orz zyx
// using namespace inline

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
ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}
template <typename T> void mine(T &a, const T &b) {if (b<a) a=b;}
template <typename T> void maxe(T &a, const T &b) {if (b>a) a=b;}

const int inf=~0U>>1, maxn=500000+10;
int n,m;
struct Edge {
	int y;
	Edge *next;
	Edge (int _y, Edge* _next) : y(_y), next(_next) {}
}*h[maxn];
int p[maxn][20];
int q[maxn], dep[maxn];
bool v[maxn];

void Add_Edge(int x,int y) {
	h[x]=new Edge(y,h[x]);
}

void PreWork() {
	fill(p,-1);
	int r=1;q[0]=0, dep[0]=0, v[0]=1;
	rep(i,r) {
		int x=q[i];
		ForE(e,x) {
			int y=e->y;
			if (!v[y]) {
				v[y]=1, dep[y]=dep[x]+1;
				p[y][0]=x;
				q[r++]=y;
			}
		}
		For(j,1,19) 
			if (p[x][j-1]!=-1) p[x][j]=p[p[x][j-1]][j-1];
			else break;
	}
}

int lca(int u,int v) {
	if (dep[u]<dep[v]) swap(u,v);
	if (dep[u]!=dep[v]) 
		repD(i,20) if (dep[u]-dep[v]>=(1<<i)) u=p[u][i];
	if (u==v) return u;
	repD(i,20) if (p[u][i]!=p[v][i]) u=p[u][i], v=p[v][i];
	return p[u][0];
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n-1) {
		int a=gi-1, b=gi-1;
		Add_Edge(a,b), Add_Edge(b,a);	
	}
	
	PreWork();
	
	rep(i,m) {
		int x=gi-1, y=gi-1, z=gi-1;
		int a=lca(x,y), b=lca(x,z), c=lca(y,z), d=lca(a,z);
		int ans=dep[a], ansi=a;
		if (dep[b]>ans) ans=dep[b], ansi=b;
		if (dep[c]>ans) ans=dep[c], ansi=c;
		ans=dep[x]+dep[y]+dep[z]-2*dep[d]-ans;
		printf("%d %d\n", ansi+1, ans);
	}
	
	return 0;
}
