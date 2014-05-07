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

const int inf=~0U>>1, maxe=1000000+10, maxp=400+10;
int n, f, d;

struct Edge {
	int y,f;
	Edge *next, *r;
};

struct Dinic {
	int S,T,n;
	int delta;
	Edge *h[maxp], *cur[maxp], mem[maxe], *C;
	int d[maxp], q[maxp];
	void init(int _s,int _t,int _n) {
		S=_s, T=_t, n=_n;
		fill(h,0);
		C=mem;
	}
	Edge *makeedge(int x,int y,int f) {
		C->next=h[x], C->y=y, C->f=f;
		return C++;
	}
	void Add_Edge(int x,int y,int f) {
		//printf("%d %d\n", x, y);
		Edge *e1=h[x]=makeedge(x,y,f), *e2=h[y]=makeedge(y,x,0);
		e1->r=e2, e2->r=e1;
	}
	bool Build() {
		fill(d,-1);
		d[S]=0, q[0]=S;int r=1;
		rep(i,r) {
			int x=q[i];
			ForE(e,x) if (e->f) {
				int y=e->y;
				if (d[y]>=0) continue;
				d[y]=d[x]+1;
				if (y==T) return 1;
				q[r++]=y;
			}
		}
		return 0;
	}
	bool Find(int x,int now_flow) {
		if (x==T) {
			delta=now_flow;
			return 1;
		}
		for (Edge *e=cur[x]; e; e=e->next) {
			cur[x]=e;
			int y=e->y;
			if (e->f && d[y]==d[x]+1 && Find(y, min(now_flow, e->f))) {
				e->f-=delta, e->r->f+=delta;
				return 1;
			}
		}
		return 0;
	}
	int Run() {
		int ans=0;
		while (Build()) {
			
			rep(i,n) cur[i]=h[i];
			while (Find(S,inf))
				ans+=delta;
		}
		return ans;
	}
}A;

int main() {
	setIO("test");
	
	n=gi, f=gi, d=gi;
	int s=0, t=n*2+f+d+1;
	A.init(s,t,t+1);
	rep(i,f) A.Add_Edge(s,i+1,1);
	rep(i,d) A.Add_Edge(i+f+n*2+1,t,1);
	
	rep(i,n) {
		int a=gi, b=gi;
		rep(j,a) {
			int x=gi;
			A.Add_Edge(x,i+f+1,1);
		}
		rep(j,b) {
			int x=gi;
			A.Add_Edge(i+f+n+1,x+f+n*2,1);
		}
		A.Add_Edge(i+f+1, i+f+n+1, 1);
	}
	printf("%d\n", A.Run());
	
	return 0;
}
