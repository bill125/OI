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

const int inf=~0U>>1,maxn=100000+10;
const ll lnf=2147483648LL*2147483647LL;
int n,m,o;
int dep[maxn], p[maxn][20], q[maxn], father[maxn], num[maxn], b[maxn];
ll f[maxn][20], limit[maxn];
bool v[maxn];

// 并查集
int find(int x) {
	if (father[x]!=x) father[x]=find(father[x]);
	return father[x];
}
void merge(int x,int y) {
	x=find(x), y=find(y);
	if (x==y) return;
	father[y]=x;
}

struct Edge {
	int y;ll v;
	Edge *next;
	Edge (int _y,ll _v,Edge *_next) : y(_y), v(_v), next(_next) {}
}*h[maxn],*h2[maxn];
struct E_Edge {
	int x,y;ll v;
	E_Edge(int _x,int _y,ll _v) : x(_x), y(_y), v(_v) {}
	bool operator<(const E_Edge &b) const {
		return v<b.v;
	}
};
struct Tag {
	int x,i;
	Tag *r, *next;
	Tag (int _x,int _i,Tag *_next) : x(_x), i(_i), next(_next) {}
}*hTag[maxn];
priority_queue<E_Edge> E;

void Add_Edge(int x,int y,ll v) {
	h[x]=new Edge(y,v,h[x]);
	h[y]=new Edge(x,v,h[y]);
}
void Add_Edge2(int x,int y,ll v) {
	h2[x]=new Edge(y,v,h2[x]);
	h2[y]=new Edge(x,v,h2[y]);
}

void Add_Tag(int i,int x,int y) {
	Tag *t1=hTag[y]=new Tag(y,i,hTag[y]);
	Tag *t2=hTag[x]=new Tag(x,i,hTag[x]);
	t1->r=t2, t2->r=t1;
}
ll calc(int x,int y) {
	ll res=lnf;
	int t=dep[y]-dep[x],k=0;
	while (t) {
		if (t&1) {
			res=min(res,f[y][k]);
			y=p[y][k];
		}
		t>>=1, ++k;
	}
	return res;
}
void Tarjan(int x) {
	rep(j,20) {
		if (p[x][j]==-1) break;
		p[x][j+1]=p[p[x][j]][j];
		f[x][j+1]=min(f[x][j], f[p[x][j]][j]);
	}
	v[x]=1;
	ForE(i,x) {
		int y=i->y;
		if (!v[y]) {
			Tarjan(y);
			merge(x,y);
		}
	}
	for (Tag *i=hTag[x];i;i=i->next) {
		int y=i->r->x;
		if (v[y]) {
			int an=find(i->r->x);
			ll t=calc(an,x);
			t=min(t,calc(an,y));
			limit[i->i]=t;
		}
	}
}

int main() {
	setIO("test");
	
	n=gi, m=gi, o=gi;
	rep(i,n) num[i]=gi-1;
	rep(i,n) b[i]=gi;
	fill(h,0);
	rep(i,m) {
		int u=gi-1, v=gi-1;ll w=gi;
		Add_Edge(u,v,w);
	}
	rep(i,o) {
		int x=gi-1;
		Add_Edge(x,n,lnf);
	}
	fill(v,0), v[0]=1;
	q[0]=0, dep[0]=0;
	fill(f,-1), fill(p,-1);
	rep(i,n) {
		if (o==0 && i==n-1) break;
		int x=q[i];
		ForE(j,x) E.push(E_Edge(x,j->y,j->v));
		
		E_Edge now(0,0,0);
		while (1) {
			now=E.top();
			E.pop();
			if (!v[now.y]) break;
		}
		int a=now.x, b=now.y;
		v[b]=1, q[i+1]=b;
		dep[b]=dep[a]+1;
		Add_Edge2(a,b,now.v);
		f[b][0]=now.v,p[b][0]=a;
	}
	
	rep(i,n+1) h[i]=h2[i];
	fill(hTag,0);
	fill(limit,-1);
	rep(i,n-1) Add_Tag(i,num[i],num[i+1]);	
	
	fill(v,0);
	rep(i,n+1) father[i]=i;
	
	Tarjan(0);
	ll now=0;
	rep(i,n) {
		ll t=b[num[i]];
		if (t>0) {
			now+=t;
		}
		else {
			t=-t;
			if (now<=t) {
				printf("%lld\n", now);
				now=0;
			}
			else {
				printf("%lld\n", t);
				now-=t;
			}
		}
		now=min(now,limit[i]);
	}
	
	return 0;
}
