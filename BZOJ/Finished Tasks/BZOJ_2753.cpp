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
typedef pair<ll,int> Pair;
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

const int inf=~0U>>1, maxn=100000+10, maxe=2000000+10;
int n, m;
int a[maxn], f[maxn];
ll d[maxn];
bool v[maxn];
struct Edge {
	int y;ll w;
	Edge *next;
	Edge (int _y,ll _w,Edge *_next) : y(_y), w(_w), next(_next) {}
}*h[maxn];

void Add_Edge(int x,int y,ll c) {
	h[x]=new Edge(y, c, h[x]);
}

queue<int> s;
struct Ele {
	int x, y; ll w;

	Ele(int _x,int _y,ll _w) : x(_x), y(_y), w(_w) {}
	Ele () {}
}E[maxe];
bool cmp(const Ele &u, const Ele &v ) {
	return a[u.y]>a[v.y] || (a[u.y]==a[v.y] && u.w<v.w); 
}

int find(int x) { return (f[x]==x)?f[x]:(f[x]=find(f[x])); }
void merge(int x,int y) { x=find(x), y=find(y), f[y]=x; }

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,n) a[i]=gi, f[i]=i;
	int e=0;
	rep(i,m) {
		int x=gi-1, y=gi-1;ll w=gi;
		if (a[x]>=a[y]) Add_Edge(x, y, w), E[e++]=Ele(x, y, w);
		if (a[y]>=a[x]) Add_Edge(y, x, w), E[e++]=Ele(y, x, w);
	}
	
	int ansv=0;ll answ=0;
	fill(v, 0);v[0]=1;
	for (s.push(0); !s.empty(); s.pop()) {
		int x=s.front();
		ForE(e,x) if (!v[e->y]) v[e->y]=1, s.push(e->y);
		++ansv;
	}
	sort(E, E+e, cmp);
	rep(i,e) {
		if (!v[E[i].x] || !v[E[i].y]) continue;
		if (find(E[i].x) == find(E[i].y)) continue;
		answ+=E[i].w;
		merge(E[i].x, E[i].y);
	}
	
	printf("%d %lld\n", ansv, answ);
	
	return 0;
}
