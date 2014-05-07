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

const int inf=~0U>>1, maxn=10000+10, maxm=maxn, maxp=30000, maxe=100000+10;
int n,m;
int x[maxm], y[maxm];
struct Dinic {
	int n,s,t,delta;
	struct Edge {
		int y,f;
		Edge *r,*next;
		Edge () {}
		Edge (int _y,int _f,Edge *_next) : y(_y), f(_f), next(_next) {} 
	}*h[maxp], *cur[maxp], mem[maxe], *c;
	int d[maxp],q[maxp];
	void init(int _n, int _s,int _t) {
		fill(h, 0);
		n=_n, s=_s, t=_t, c=mem;
	}
	Edge *makeedge(int x,int y,int f) {
		c->y=y, c->f=f, c->next=h[x];
		return c++;
	}
	void Add_Edge(int x,int y,int f) {
		h[x]=makeedge(x,y,f),h[y]=makeedge(y,x,0);
		h[x]->r=h[y],h[y]->r=h[x];
	}
	bool Build() {
		fill(d,127);d[s]=0;
		q[0]=s;int r=1;
		rep(i,r) {
			int x=q[i];
			ForE(e,x) if (e->f) {
				int y=e->y;
				if (d[x]+1<d[y]) {
					d[y]=d[x]+1;
					if (y==t) return 1;
					q[r++]=y;
				}
			}
		}
		return 0;
	}
	bool Find(int x,int now_flow) {
		if (x==t) {
			delta=now_flow;
			return 1;
		}
		for (Edge *e=cur[x]; e; e=e->next) if (e->f) {
			cur[x]=e;
			int y=e->y;
			if (d[x]+1==d[y] && Find(y,min(now_flow,e->f))) {
				e->f-=delta,e->r->f+=delta;
				return 1;
			}
		}
		return 0;
	}
	int MaxFlow() {
		int res=0;
		while (Build()) {
			rep(i,n) cur[i]=h[i];
			while (Find(s,inf)) res+=delta;
		}			
		return res;
	}
}A;

bool ok(int p) {
	int s=0, t=n+m+1;
	A.init(t+1, s, t);
	For(i,1,n) A.Add_Edge(s, i, p);
	rep(i,m) A.Add_Edge(x[i], i+n+1, 1), A.Add_Edge(y[i], i+n+1, 1), A.Add_Edge(i+n+1, t, 1);
	return A.MaxFlow()==m;
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	rep(i,m) x[i]=gi, y[i]=gi;
	
	int l=0, r=m;
	while (l+1 < r) {
		int m=(l+r)>>1;
		if (ok(m)) r=m;
		else l=m;
	}
	printf("%d\n", r);
	
	return 0;   
}
