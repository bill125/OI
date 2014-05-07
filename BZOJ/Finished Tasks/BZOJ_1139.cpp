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

const int inf=~0U>>1, maxn=300+10, maxe=6000+10, maxM=10000+10;
int n,m,p,b;
int sword[maxn];
int f[maxn][maxM];
struct Ele {
	int x,M,f;
	Ele() {}
	Ele(int _x,int _M, int _f) : x(_x), M(_M), f(_f) {}
};
deque<Ele> q;

struct Edge {
	int y,t,M;
	Edge *next;
}*h[maxn], mem[maxe], *E=mem;
Edge *makeedge(int x,int y,int t,int M) {
	E->next=h[x], E->y=y, E->t=t, E->M=M;
	return E++;
}
void Add_Edge(int x,int y,int t,int M) {
	h[x]=makeedge(x,y,t,M);
	h[y]=makeedge(y,x,t,M);
}

int main() {
	setIO("test");
	
	n=gi, m=gi, p=gi, b=gi;
	rep(i,b) {
		int id=gi-1, l=gi;
		rep(j,l) {
			int k=gi-1;
			sword[id]|=1<<k;
		}
	}
	rep(i,m) {
		int x=gi-1, y=gi-1, t=gi, l=gi;
		int M=0;
		rep(j,l) {
			int k=gi-1;
			M|=1<<k;
		}
		Add_Edge(x,y,t,M);
	}
	q.clear();
	rep(i,n) rep(j,(1<<p)) f[i][j]=inf;
	f[0][sword[0]]=0;
	q.pb(Ele(0,sword[0],0));
	while (!q.empty()) {
		Ele t;
		while (!q.empty()) {
			t=q.front(); q.pop_front();
			if (f[t.x][t.M]==t.f) break;
		}
		if (f[t.x][t.M]!=t.f) break;
		int x=t.x, M=t.M;
		ForE(e,x) if ((e->M&M)==e->M) {
			int y=e->y;
			int tM=M|sword[y];
			if (f[x][M]+e->t<f[y][tM]) {
				f[y][tM]=f[x][M]+e->t;
				if (q.empty() || f[y][tM]<q.front().f) q.push_front(Ele(y,tM,f[y][tM]));
				else q.push_back(Ele(y,tM,f[y][tM]));
			}
		}
	}
	
	int ans=inf;
	rep(i,(1<<p)) ans=min(ans, f[n-1][i]);
	printf("%d\n", (ans==inf)?-1:ans);
	
	return 0;
}
