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
#include <cmath>

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

const int inf=~0U>>1, maxp=100+10, maxm=100000+10;
const db eps=0.00001;
int n,m;
int a[maxm], b[maxm];
db c[maxm];
db p;

struct Dinic {
	int n,s,t;
	db delta;
	struct Edge {
		int y; db f;
		Edge *r,*next;
	}*h[maxp], *cur[maxp], mem[maxm*4], *e;
	int d[maxp],q[maxp];
	void init(int _n, int _s,int _t) {
		e=mem;
		n=_n, s=_s, t=_t;
		fill(h,0);
	}
	Edge *makeedge(int x,int y,db f) {
		e->y=y, e->next=h[x], e->f=f;
		return e++;
	}
	void Add_Edge(int x,int y,db f) {
		h[x]=makeedge(x,y,f),h[y]=makeedge(y,x,0);
		h[x]->r=h[y],h[y]->r=h[x];
	}
	bool Build() {
		rep(i,n) d[i]=inf;d[s]=0;
		q[0]=s;int r=1;
		rep(i,r) {
			int x=q[i];
			ForE(e,x) if (!(e->f<eps)) {
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
	bool Find(int x,db now_flow) {
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
	db MaxFlow() {
		db res=0;
		while (Build()) {
			rep(i,n) cur[i]=h[i];
			while (Find(s,inf)) res+=delta;
		}			
		return res;
	}
}A;

db check(db t) {
	A.init(n, 0, n-1);
	rep(i,m) {
		A.Add_Edge(a[i], b[i], min(c[i], t));		
	}
	return A.MaxFlow();
}

int main() {
	setIO("test");
	
	n=gi, m=gi; scanf("%lf", &p);
	rep(i,m) a[i]=gi-1, b[i]=gi-1, c[i]=gi;
	db ans1=check(100000);
	
	db l=0, r=50001;
	while (l + 0.00001 < r) {
		db m=(l+r) / 2;
		if (abs (check(m) - ans1) <= eps) r=m;
		else l=m;
	}
	printf("%.0f\n%.6f\n", ans1, r*p);
	
	return 0;   
}
