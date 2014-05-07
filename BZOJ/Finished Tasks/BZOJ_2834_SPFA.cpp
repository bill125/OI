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

const int inf=~0U>>1,maxn=500000+10,maxm=1000000+10;
int n,m;
int x[maxm],y[maxm],num[maxm];
int d[maxn];
map<int,int> f[maxn];
struct Edge {
	int y,v;
	Edge *next;
	Edge () {}
	Edge (int _y,int _v,Edge *_next) : y(_y), v(_v), next(_next) {}
}*h[maxn]={0};

void Add_Edge(int x,int y,int l) {
	h[x]=new Edge(y,l,h[x]);
	h[y]=new Edge(x,l,h[y]);
}

bool cmp1(int a,int b) {
	return (x[a]<x[b] || x[a]==x[b] && y[a]<y[b]);
}
bool cmp2(int a,int b) {
	return (y[a]<y[b] || y[a]==y[b] && x[a]<x[b]);
}

int spfa(int s,int t) {
	deque<Pair> q;q.clear();
	fill(d,-1);d[s]=0;
	q.pb(mp(s,0));

	while (1) {
		Pair now=mp(0,-10);
		while (!q.empty()) {
			now=q.front();
			q.pop_front();
			if (now.second==d[now.first]) break;
		}
		if (now.second!=d[now.first]) break;
		int x=now.first;
		ForE(i,x) {
			int y=i->y;
			if (d[y]==-1 || d[x]+i->v<d[y]) {
				d[y]=d[x]+i->v;
				if (q.empty() || d[y]<q.front().second)
					q.push_front(mp(y,d[y]));
				else 
					q.push_back(mp(y,d[y]));
			}
		}
		//printf("%d\n", now.first);
	}
	return d[t];
}

int main() {
	setIO("test");
	
	int tag=0;
	n=gi, m=gi;
	rep(i,m) {
		x[i]=gi, y[i]=gi;
		f[x[i]][y[i]]=tag++;
	}
	int sx=gi, sy=gi, dx=gi, dy=gi;
	if (!f[sx].count(sy)) x[m]=sx, y[m]=sy, f[sx][sy]=tag++, ++m;
	if (!f[dx].count(dy)) x[m]=dx, y[m]=dy, f[dx][dy]=tag++, ++m;
	
	rep(i,m) num[i]=i;
	sort(num, num+m, cmp1);
	For(i,1,m-1) {
		int a=num[i], b=num[i-1];
		if (x[a]==x[b]) Add_Edge(a,b,(y[a]-y[b])*2);
	}
	sort(num, num+m, cmp2);
	For(i,1,m-1) {
		int a=num[i], b=num[i-1];
		if (y[a]==y[b]) Add_Edge(a+m,b+m,(x[a]-x[b])*2);
	}
	rep(i,m) Add_Edge(i,i+m,1);
	
	int s=m*2, t=m*2+1;
	Add_Edge(s,f[sx][sy],0),Add_Edge(s,f[sx][sy]+m,0);
	Add_Edge(t,f[dx][dy],0),Add_Edge(t,f[dx][dy]+m,0);
	
	printf("%d\n", spfa(s,t));
	
	return 0;
}
