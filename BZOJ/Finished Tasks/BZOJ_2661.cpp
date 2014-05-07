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
ll gI() {char c=getchar();while ((c<'0' || c>'9')&&c!='-') c=getchar();ll flag=1,p=0;if (c=='-') flag=-1,c=getchar();while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p*flag;}
int gs(char *C) {char c=getchar();while (c==' ' || c=='\n') c=getchar();int l=0;while (c!=' ' && c!='\n') C[l++]=c,c=getchar();C[l]=0;return l;}
template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i],(i==n-1)?'\n':' ');}

const int inf=~0U>>1, maxp=3000+10, maxe=4000000+10;

struct Edge {
	int y,f,c;
	Edge *next, *r;
};

struct CostFlow {
	int n,s,t,delta,now_flow;
	Edge *h[maxp], *prev[maxp], mem[maxe], *C;
	deque<Pair> q;
	int d[maxp];
	Edge* makeedge(int x,int y,int f,int c) {
		C->y=y, C->next=h[x], C->f=f, C->c=c;
		return C++;
	}
	void Add_Edge(int x,int y,int f,int c) {
		Edge *e1=h[x]=makeedge(x,y,f,c), *e2=h[y]=makeedge(y,x,0,-c);
		e1->r=e2, e2->r=e1;
	}
	void init(int _s,int _t,int _n) {
		s=_s, t=_t, n=_n;
		fill(h,0), C=mem;
	}
	bool Find() {
		q.clear();
		q.pb(mp(s,0));
		fill(d,-1), d[s]=0;
		while (!q.empty()) {
			Pair tmp=q.front();
			q.pop_front();
			if (d[tmp.first]!=tmp.second) continue;
			int x=tmp.first;
			ForE(e,x) if (e->f) {
				int y=e->y;
				if (d[y]==-1 || d[x]+e->c<d[y]) {
					d[y]=d[x]+e->c;
					prev[y]=e;
					if (q.empty() || d[y]<q.front().second) q.push_front(mp(y,d[y]));
					else q.push_back(mp(y,d[y]));
				}
			}
		}
		if (d[t]==-1) return 0;
		now_flow=inf;
		for (int x=t; x!=s; x=prev[x]->r->y) now_flow=min(now_flow, prev[x]->f);
		for (int x=t; x!=s; x=prev[x]->r->y) prev[x]->f-=now_flow, prev[x]->r->f+=now_flow;
		delta=now_flow*d[t];
		return 1;
	}
	Pair Run() {
		int ans1=0, ans2=0;
		while (Find())
			ans1+=now_flow, ans2+=delta;
		return mp(ans1, ans2);
	}
}A;

int gcd(int a,int b) {
	if (a==0) return b;
	return gcd(b%a, a);
}

int main() {
	setIO("test");
	
	int a=gi, b=gi, n=1000;
	int s=0, t=2001;
	A.init(s, t, 2002);
	For(i,a,b) For(j,a,b) {
		if (i==j) continue;
		int x=max(i,j), y=min(i,j);
		int t=(int)sqrt((db)x*x-y*y);
		if (t*t==x*x-y*y && gcd(y,t)==1) {
			A.Add_Edge(i, j+n, 1, -(i+j));
		}
	}
	For(i,a,b) 
		A.Add_Edge(s, i, 1, 0),
		A.Add_Edge(i+n, t, 1, 0);
	
	Pair ans=A.Run();
	printf("%d %d\n", ans.first/2, -ans.second/2);
	
	return 0;
}
