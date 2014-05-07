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

const int maxe=200000, maxn=40+10, maxp=2000+10;
const ll inf=10000000000000ll; 
ll n,m;
ll a[maxn][maxn];
int dx[4]={1,0,0,-1}, dy[4]={0,1,-1,0};
struct Edge {
	int y; ll f;
	Edge *next, *r;
};

struct Dinic {
	int S,T,n;
	ll delta;
	Edge *h[maxp], *cur[maxp], mem[maxe], *C;
	int d[maxp], q[maxp];
	void init(int _s,int _t,int _n) {
		S=_s, T=_t, n=_n;
		fill(h,0);
		C=mem;
	}
	Edge *makeedge(int x,int y,ll f) {
		C->next=h[x], C->y=y, C->f=f;
		return C++;
	}
	void Add_Edge(int x,int y,ll f) {
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
	bool Find(int x,ll now_flow) {
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
	ll Run() {
		ll ans=0;
		while (Build()) {
			
			rep(i,n) cur[i]=h[i];
			while (Find(S,inf))
				ans+=delta;
		}
		return ans;
	}
}A;

int code(int x,int y) {	return x*m+y+1; }
bool valid(int x,int y) { return x>=0 && x<n && y>=0 && y<m; }
bool ok(ll x) {
	int s=0, t=n*m+1;
	ll sum=0;
	A.init(s,t,n*m+2);
	rep(i,n) rep(j,m) {
		if ((i+j)&1) A.Add_Edge(code(i,j),t,x-a[i][j]), sum+=x-a[i][j];
		else {
			A.Add_Edge(s,code(i,j),x-a[i][j]);
			rep(k,4) {
				int tx=i+dx[k], ty=j+dy[k];
				if (valid(tx, ty)) A.Add_Edge(code(i,j), code(tx,ty), inf);
			}
		}

	}
	ll ans=A.Run();
	if (ans==sum) return 1;
	return 0;
}

int main() {
	setIO("test");
	
	for (int Td=gi; Td--; ) {
		n=gi,m=gi;
		ll cnt1=0, cnt2=0, s1=0, s2=0, maxa=0;
		rep(i,n) rep(j,m) {
			a[i][j]=gi;
			maxa=max(maxa,a[i][j]);
			if ((i+j)&1) ++cnt1, s1+=a[i][j];
			else ++cnt2, s2+=a[i][j];
		}
		if (cnt1!=cnt2) {
			if ((s1-s2)%(cnt1-cnt2)!=0) { puts("-1"); continue; }
			ll x=(s1-s2)/(cnt1-cnt2);
			if (x<maxa) { puts("-1"); continue; }
			if (ok(x)) printf("%lld\n", (x*n*m-s1-s2)>>1);
			else puts("-1");
		}
		else {
			if (s1!=s2) { puts("-1"); continue; }
			ll l=maxa, r=10000000000LL;
			while (l+1<r) {
				ll m=(l+r)>>1;
				if (ok(m)) r=m;
				else l=m;
			}
			if (ok(r)) printf("%lld\n", (r*n*m-s1-s2)>>1);
			else puts("-1");
		}
	}
	
	return 0;
}
