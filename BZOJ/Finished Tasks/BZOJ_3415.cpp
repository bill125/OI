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

const int inf=~0U>>1,maxn=100000+10, maxp=maxn;
int n,m,s,a,b;
int dist[maxn], ans[maxn], pre[maxn];
struct bfs {
	int n;
	bool v[maxp];
	int q[maxp];
	struct Edge {
		int y, v;
		Edge *next, *pre;
	}*E, *h[maxp], *h2[maxp];
	struct Ele {
		int x, d;
		bool operator< (const Ele &t) const{
			return d>t.d;
		}
		Ele(int _x,int _d) : x(_x), d(_d) {}
		Ele() {}
	};
	void init(int _n) {
		n=_n;
		fill(h, 0), fill(h2, 0);
	}
	void Add_Edge(int x,int y,int v) {
		E=new Edge;
		E->next=h[x], E->v=v, E->y=y, E->pre=0;
		if (h[x]) h[x]->pre=E;
		h[x]=E;
		
		E=new Edge;
		E->next=h2[x], E->v=v, E->y=y, E->pre=0;
		if (h2[x]) h2[x]->pre=E;
		h2[x]=E;
	}
	void Run(int s,int d[]) {
		fill(v, 0);
		rep(i,n) d[i]=inf;
		d[s]=0, q[0]=s, v[s]=1;
		int r=1;
		rep(i,r) {
			int x=q[i];
			ForE(e,x) if (!v[e->y]) {
				d[e->y]=d[x]+1;
				q[r++]=e->y;
				v[e->y]=1;
			}
		}
	}
	void del(int x,Edge *e) {
		if (e==h2[x]) h2[x]=e->next;
		if (e->pre) e->pre->next=e->next;
		if (e->next) e->next->pre=e->pre;
	}
	void Run2(int s,int d[]) {
		rep(i,n) d[i]=inf;
		fill(v,0);
		d[s]=0, q[0]=s, v[s]=1;
		int r=1;
		fill(pre, -1);
		rep(i,r) {
			int x=q[i];
			ForE(e,x) pre[e->y]=x;
			ForE(e,x) for (Edge *e2=h2[e->y]; e2; e2=e2->next) 
				if (pre[e2->y]!=x && !v[e2->y]) {
					v[e2->y]=1;
					d[e2->y]=d[x]+1;
					q[r++]=e2->y;
					del(e->y, e2);
				}
		}
	}
}A;

int main() {
	setIO("test");
	
	n=gi, m=gi, s=gi-1, a=gi, b=gi;
	A.init(n);
	rep(i,m) {
		int x=gi-1, y=gi-1;
		A.Add_Edge(x,y,1), A.Add_Edge(y,x,1);
	}
	A.Run(s, dist);
	if (b>a*2) b=a*2;
	rep(i,n) ans[i]=(dist[i]>>1)*b+(dist[i]&1)*a;
	
	if (b<a) {
		A.Run2(s, dist);
		rep(i,n) if (dist[i]!=inf) ans[i]=min(ans[i], dist[i]*b);
	}
	rep(i,n) printf("%d\n", ans[i]);
	
	return 0;
}
