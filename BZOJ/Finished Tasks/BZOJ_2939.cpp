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

const int inf=~0U>>1, maxp=10000+10, maxe=1000000;
int n;
struct dinic {
	int n, s, t, delta;
	int q[maxp], d[maxp];
	struct Edge {
		int y, f;
		Edge *next, *r;
	}mem[maxe], *h[maxp], *e, *cur[maxp];
	void init(int _n,int _s,int _t) {
		n=_n, s=_s, t=_t;
		rep(i,n) h[i]=0;
		e=mem;
	}
	Edge *makeedge(int a,int b,int f) {
		e->y=b, e->f=f, e->next=h[a];
		return e++;
	}
	void Add_Edge(int x,int y,int c) {
		h[x]=makeedge(x, y, c), h[y]=makeedge(y, x, 0);
		h[x]->r=h[y], h[y]->r=h[x];
	}
	bool build() {
		fill(d, 127);d[s]=0;
		int r=1;q[0]=s;
		rep(i,r) {
			int x=q[i];
			ForE(e,x) if (e->f) {
				int y=e->y;
				if (d[y]>d[x]+1) {
					d[y]=d[x]+1;
					if (y==t) return 1;
					q[r++]=y;
				}
			}
		}
		return 0;
	}
	bool find(int x,int now_flow) {
		if (x==t) {
			delta=now_flow;
			return 1;
		}
		for (Edge *e=cur[x]; e; e=e->next) if (e->f) {
			cur[x]=e;
			int y=e->y;
			if (d[y] == d[x]+1 && find (y, min(now_flow, e->f))) {
				e->f-=delta, e->r->f+=delta;
				return 1;
			}
		}
		return 0;
	}
	int MaxFlow() {
		int res=0;
		while (build()) {
			rep(i,n) cur[i]=h[i];
			while (find(s, inf)) res+=delta;
		}
		return res;
	}
}A;

int main() {
	setIO("test");
	
	n=gi;
	int s=0, t=n*2-1;
	A.init(n*2, s, t);
	rep(i,n) A.Add_Edge(i, i+n, (i==0||i==n-1)?inf:1);
	rep(i,n-1) {
		int k=gi;
		rep(j,k) {
			int x=gi-1;
			A.Add_Edge(i+n, x, 1);
		}
	}
	printf("%d\n", A.MaxFlow());
	
	return 0;   
}
