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

const int inf=~0U>>1, maxn=100+10, maxp=100+10, maxe=1000000+10;
int n,a1,b1,a2,b2,an,bn;
char c[maxn][maxn];

struct Dinic {
	int n,S,T,delta;
	struct Edge {
		int y,f;
		Edge *r,*next;
		Edge () {}
		Edge (int _y,int _f,Edge *_next) : y(_y), f(_f), next(_next) {} 
	}*h[maxp], *cur[maxp], mem[maxe], *C;
	int d[maxp],q[maxp];
	void init(int _n,int _S,int _T) {
		n=_n, S=_S, T=_T;
		C=mem;
		fill(h,0);
	}
	Edge *makeedge(int x,int y,int f) {
		C->next=h[x], C->y=y, C->f=f;
		return C++;
	}
	void Add_Edge(int x,int y,int f) {
		Edge *e1=h[x]=makeedge(x,y,f), *e2=h[y]=makeedge(y,x,0);
		e1->r=e2, e2->r=e1;
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
					if (y==T) return 1;
					q[r++]=y;
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
			while (Find(S,inf)) 
				res+=delta;
		}
			
		return res;
	}
}A;

int main() {
	setIO("test");
	
	int all=0;
	while (scanf("%d", &n)!=EOF) {
		a1=gi, a2=gi, an=gi, b1=gi, b2=gi, bn=gi;
		rep(i,n) scanf("%s", c[i]);
		int s=n, t=n+1;
		bool flag=0;
		
		A.init(n+2, s, t);
		rep(i,n) {
			rep(j,n) {
				if (c[i][j]=='O') A.Add_Edge(i,j,1);
				if (c[i][j]=='N') A.Add_Edge(i,j,inf);
			}
		}
		A.Add_Edge(s, a1, an); A.Add_Edge(s, b1, bn);
		A.Add_Edge(a2, t, an); A.Add_Edge(b2, t, bn);
		
		flag|=A.MaxFlow()!=an+bn;	
		
		A.init(n+2, s, t);
		rep(i,n) {
			rep(j,n) {
				if (c[i][j]=='O') A.Add_Edge(i,j,1);
				if (c[i][j]=='N') A.Add_Edge(i,j,inf);
			}
		}
		A.Add_Edge(s, a1, an); A.Add_Edge(s, b2, bn);
		A.Add_Edge(a2, t, an); A.Add_Edge(b1, t, bn);
		
		flag|=A.MaxFlow()!=an+bn;
		
		if (!flag) puts("Yes");
		else puts("No");
	}
	
	return 0;
}
