//Author: bill123

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
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)>(b))?(b):(a))
#define pb push_back
#define mp make_pair
#define v1 first
#define v2 second
#define gi gI()

void setIO(string NAME) {
	#ifndef ONLINE_JUDGE
	string in = NAME + ".in";
	string out = NAME + ".out";
	freopen(in.c_str(),"r",stdin);
	freopen(out.c_str(),"w",stdout);
	#endif
}
ll gI() {
	char c=getchar();
	while ((c<'0' || c>'9')&&c!='-') c=getchar();
	ll flag=1,p=0;
	if (c=='-') flag=-1,c=getchar();
	while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();
	return p*flag;
}
int gs(char *C) {
	char c=getchar();
	while (c==' ' || c=='\n') c=getchar();
	int l=0;
	while (c!=' ' && c!='\n') C[l++]=c,c=getchar();
	C[l]=0;
	return l;
}

template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i], (i==n-1) ? '\n' : ' ');}
template <typename T> void mine(T &a, const T &b) {if (b<a) a=b;}
template <typename T> void maxe(T &a, const T &b) {if (b>a) a=b;}

const int inf=~0U>>1, maxn=100000+10, maxdep=30;
int n,m,L,U;
db ans=0;
int q[maxn],son[maxn],son2[maxn],len[maxn],q2[maxn],c[maxn],p[maxn];
db sum[maxn],path[maxn],nowpath[maxn],b[maxn];
bool v[maxdep][maxn],cut[maxn],vis[maxn];
struct Edge {
	int y;
	db v;
	Edge *next;
	Edge (int _y,db _v,Edge *_next) : y(_y), v(_v), next(_next) {}	
}*h[maxn];

void Add_Edge(int x,int y,db c) {
	h[x]=new Edge(y,c,h[x]);
	h[y]=new Edge(x,c,h[y]);
}

int gettree(int x,int dep,int q[]) {
	int sz=1;
	q[0]=x,v[dep][x]=1;
	rep(i,sz) {
		int x=q[i];
		ForE(j,x) {
			int y=j->y;
			if (!v[dep][y] && !cut[y]) {
				q[sz++]=y;
				v[dep][y]=1;
				p[y]=x;
			}
		}
	}
	return sz;
}

bool calc(int s,db std) {
	nowpath[0]=0;

	int sz=1;
	q2[0]=s, vis[s]=1;
	rep(i,sz) {
		int x=q2[i];
		nowpath[i+1]=-inf;
		ForE(j,x) {
			int y=j->y;
			if (!vis[y] && !cut[y]) {
				sum[y]=sum[x]+j->v-std;
				len[y]=len[x]+1;
				vis[y]=1, q2[sz++]=y;
			}
		}
		maxe(nowpath[len[x]],sum[x]);
	}
	
	int j=U;
	int l=0, r=-1;
	rep(i,sz+1) {
		while (j>=max(L-i,0)) {
			if (path[j]!=-inf) {
				while (l<=r && b[r]<=path[j]) --r;
				++r;
				b[r]=path[j], c[r]=j;
			}
			--j;
		}
		if (c[l]>U-i) ++l;
		if (nowpath[i]!=-inf && l<=r && nowpath[i]+b[l]>=0) return 1;
	} 
	rep(i,sz+1) maxe(path[i],nowpath[i]);
	return 0;
}

void work(int s,int dep) {
	int sz=gettree(s,dep,q);
	if (sz<L||sz<2) return;
	
	rep(i,sz) v[dep][q[i]]=0;
	repD(i,sz) {
		int x=q[i];
		v[dep][x]=1, son[x]=1, son2[x]=0;
		ForE(j,x) {
			int y=j->y;
			if (v[dep][y] && !cut[y]) {
				son[x]+=son[y];
				maxe(son2[x],son[y]);
			}
		}
	}
	
	int g,MIN=inf;
	rep(i,sz) {
		int x=q[i];
		if (x==s) continue;
		int t=max(son[x],sz-son[x]);
		if (t<MIN) 
			MIN=t, g=x;
	}

	int np=p[g];
	sum[g]=len[g]=0;
	
	db l=ans, r=1000001;
	while (l+0.0001<r) {
		db m=(l+r)/2;
		rep(i,sz) path[i+1]=-inf,vis[q[i]]=0;path[0]=0;
		bool flag=0;
		cut[np]=1;
		if (calc(g,m)) flag=1;
		cut[np]=0;
		if (!flag && calc(g,m)) flag=1;
		
		if (flag) l=m;
		else r=m;
	} 
	maxe(ans,l);
	cut[np]=1;
	work(g,dep+1);
	cut[np]=0;
	cut[g]=1;
	work(s,dep+1);
	cut[g]=0;
}

int main() {
	setIO("test");
	
	n=gi;
	L=gi, U=gi;
	
	rep(i,n-1) {
		int a=gi-1, b=gi-1, c=gi;
		Add_Edge(a,b,c);
	}
	
	fill(cut,0),fill(v,0),fill(p,-1);
	work(0,0);
	printf("%.3f\n", ans);
	
	return 0;
}
