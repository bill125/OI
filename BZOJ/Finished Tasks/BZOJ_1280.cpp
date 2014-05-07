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

const int inf=~0U>>1, maxm=1000+10, maxp=100+10;
int n,m;
int f[maxm], s[maxm], last[maxm];

struct Dinic {
	int S,T,delta;
	struct Edge {
		int y,f;
		Edge *r,*next;
		Edge () {}
		Edge (int _y,int _f,Edge *_next) : y(_y), f(_f), next(_next) {} 
	}*h[maxp], *cur[maxp];
	int d[maxp],q[maxp];
	void init(int _S,int _T) {
		S=_S, T=_T;
		fill(h,0);
	}
	void Add_Edge(int x,int y,int f) {
		h[x]=new Edge(y,f,h[x]),h[y]=new Edge(x,0,h[y]);
		h[x]->r=h[y],h[y]->r=h[x];
	}
	bool Build() {
		fill(d,127);d[S]=0;
		q[0]=S;int r=1;
		rep(i,r) {
			int x=q[i];
			ForE(e,x) if (e->f) {
				int y=e->y;
				if (d[x]+1<d[y]) {
					d[y]=d[x]+1;
					q[r++]=y;
					if (y==T) return 1;
				}
			}
		}
		return 0;
	}
	bool Find(int x,int now_flow) {
		if (x==T) {
			delta=now_flow;
			return 1;
		}
		for (Edge *e=cur[x]; e; e=e->next) if (e->f) {
			int y=e->y;
			cur[x]=e;
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
			rep(i,T+1) cur[i]=h[i]; 
			while (Find(S,inf)) 
				res+=delta;
		}
			
		return res;
	}
}T;

int main() {
	setIO("test");
	
	m=gi, n=gi;
	rep(i,m) s[i]=gi, last[i]=0;
	T.init(0,n+1);
	
	For(i,1,n) {
		int l=gi;
		rep(j,l) {
			int x=gi-1;
			if (last[x]==0) T.Add_Edge(0,i,s[x]);
			else T.Add_Edge(last[x],i,inf);
			last[x]=i;
		}
		int b=gi;
		T.Add_Edge(i,n+1,b);
	}
	
	printf("%d\n", T.MaxFlow());
	
	return 0;
}
