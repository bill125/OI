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

const int inf=~0U>>1, maxn=40+10, maxp=70000+10;
int p, q, r, D;
int w[maxn][maxn][maxn], id[maxn][maxn][maxn];

struct Dinic {
	int n,s,t,delta;
	struct Edge {
		int y,f;
		Edge *r,*next;
		Edge () {}
		Edge (int _y,int _f,Edge *_next) : y(_y), f(_f), next(_next) {} 
	}*h[maxp], *cur[maxp];
	int d[maxp],q[maxp];
	void init(int _n, int _s,int _t) {
		n=_n, s=_s, t=_t;
		fill(h,0);
	}
	void Add_Edge(int x,int y,int f) {
		//printf("%d->%d %d\n", x, y, f);
		h[x]=new Edge(y,f,h[x]),h[y]=new Edge(x,0,h[y]);
		h[x]->r=h[y],h[y]->r=h[x];
	}
	bool Build() {
		rep(i,n) d[i]=inf;d[s]=0;
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

bool valid(int x,int y) {
	return x >= 0 && y >= 0 && x < p && y < q;
}

int main() {
	setIO("test");
	
	int s=0, t=1;
	int tag=2;
	
	p=gi, q=gi, r=gi;
	D=gi;
	rep(k,r) rep(i,p) rep(j,q) {
		w[i][j][k]=gi;
		id[i][j][k]=tag++;
	}
	rep(i,p) rep(j,q) id[i][j][r]=tag++;
	
	A.init(tag, s, t);
	rep(i,p) rep(j,q) rep(k,r) {
		A.Add_Edge(id[i][j][k], id[i][j][k+1], w[i][j][k]);
	}
	
	rep(i,p) rep(j,q) {
		A.Add_Edge(s, id[i][j][0], inf);
		A.Add_Edge(id[i][j][r], t, inf);
	}
	
	int dx[4]={0, -1, 1, 0};
	int dy[4]={-1, 0, 0, 1};
	rep(i,p) rep(j,q) For(c,D,r) 
		rep(k,4) {
			int tx=i+dx[k], ty=j+dy[k];
			if (valid(tx, ty)) {
				if (id[tx][ty][c-D]==s) puts("SS");
				if (id[tx][ty][c-D]==t) puts("SS");
				A.Add_Edge(id[i][j][c], id[tx][ty][c-D], inf);
			}
		}
	printf("%d\n", A.MaxFlow());
		
	return 0;   
}
