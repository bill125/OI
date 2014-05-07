//Author: bill125

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
#define cut puts("===================")

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

const int inf=~0U>>1,maxn=20000+10,maxT=40000+10,maxE=50000+10;
int n,tot;
int a[maxn], b[maxn], c[maxn], dep[maxn], len[maxn], p[maxn], an[maxn], id[maxn], son[maxn], sz[maxn];
bool v[maxn];

struct Edge {
	int y,v;
	Edge *next;
}*h[maxn],mem[maxE],*C;

Edge *makeedge(int y,int v, Edge *next) {
	C->y=y, C->v=v, C->next=next;
	return C++;
}

void Add_Edge(int x,int y,int c) {
	h[x]=makeedge(y,c,h[x]);
	h[y]=makeedge(x,c,h[y]);
}

struct sTree {
	int h;
	int a[maxT];
 
	void init(const int n) {
		for (h=1;(1<<h)<n+2; ++h) ;
		fill(a,0);
		repD(i,(1<<h)) refresh(i);
	}
	void refresh(const int&x) {
		a[x]=max(a[x<<1],a[(x<<1)+1]);
	}	 
	void Update(int x) {
		for (x>>=1;x;x>>=1) refresh(x);
	}	 
	int Ask(int l,int r) {
		int res=-inf;
		l+=(1<<h)-1,r+=(1<<h)+1;
		while (l+1<r) {
			if (!(l&1)) res=max(res,a[l^1]);
			if (r&1) res=max(res,a[r^1]);
			l>>=1, r>>=1;
		}
		return res;
	}	 
	void Chg(int x,int c) {
		x+=(1<<h);
		a[x]=c;
		Update(x);
	}
}T;

int ask(int u,int v) {
	int res=-inf;
	while (an[u]!=an[v]) {
		int tu=(an[u]==u)?p[u]:an[u];
		int tv=(an[v]==v)?p[v]:an[v];
		if (dep[tu]>=dep[tv] && u) {
			if (tu==an[u]) maxe(res,T.Ask(id[tu]+1,id[u]));
			else maxe(res,len[u]);
			u=tu;
		}
		else {
			if (tv==an[v]) maxe(res,T.Ask(id[tv]+1,id[v]));
			else maxe(res,len[v]);
			v=tv;
		}
	}
	
	if (u!=v) {
		if (dep[u]>dep[v]) swap(u,v);
		if (an[u]!=an[v]) maxe(res,len[v]);
		else maxe(res,T.Ask(id[u]+1,id[v]));
	}
	return res;
}

void calc(int x) {
	v[x]=1, sz[x]=1;
	int MAX=-1;son[x]=-1;
	ForE(i,x) {
		int y=i->y;
		if (!v[y]) {
			dep[y]=dep[x]+1, p[y]=x, len[y]=i->v;
			calc(y);
			sz[x]+=sz[y];
			if (sz[y]>MAX) 	MAX=sz[y], son[x]=y;
		}
	}
}

void work(int x,int a) {
	an[x]=a, id[x]=++tot;;
	if (son[x]!=-1) work(son[x],a); 
	ForE(i,x) if (i->y!=p[x] && i->y!=son[x]) work(i->y,i->y);
}

void chg(int u,int c) {
	int x;
	if (a[u]==p[b[u]]) x=b[u];
	else x=a[u];
	if (x==an[x]) len[x]=c;
	else T.Chg(id[x],c);
}

int main() {
	setIO("test");
	
	for (int Td=gi; Td--;) {
		n=gi;
		fill(h,0);
		C=mem, tot=0;
		rep(i,n-1) {
			a[i]=gi-1, b[i]=gi-1, c[i]=gi;
			Add_Edge(a[i],b[i],c[i]);
			//printf("%d %d\n", a[i], b[i]);
		}
		T.init(n);
		fill(v,0);
		calc(0);
		work(0,0);
		rep(i,n) if (son[i]!=-1) T.Chg(id[son[i]],len[son[i]]);

		char c[10];
		while (gs(c)) {
			if (c[0]=='D') break;
			if (c[0]=='Q') {
				int u=gi-1, v=gi-1;
				printf("%d\n", ask(u,v));
			}
			else {
				int u=gi-1, c=gi;
				chg(u,c);
			}
		}
	}
	
	return 0;
}
