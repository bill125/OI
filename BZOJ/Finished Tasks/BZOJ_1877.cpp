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

const int inf=~0U>>1, maxp=1000+10, maxe=200000+10;
int n,m;
struct Edge {
	int y,f,c;
	Edge *next, *r;
};

struct CostFlow {
	int n,s,t,delta;
	deque<Pair> q;
	int d[maxp];
	Edge *h[maxp], mem[maxe], *C, *prev[maxp];
	Edge *makeedge(int x,int y,int f,int c) {
		C->y=y, C->next=h[x], C->f=f, C->c=c;
		return C++;
	}
	void Add_Edge(int x,int y,int f,int c) {
		//printf("%d %d\n", x, y);
		Edge *e1=h[x]=makeedge(x,y,f,c), *e2=h[y]=makeedge(y,x,0,-c);
		e1->r=e2, e2->r=e1;
	}
	void init(int _s,int _t,int _n) {
		s=_s, t=_t, n=_n;
		fill(h,0), C=mem;
	}
	bool Find() {
		fill(d,-1);
		q.clear(), q.pb(mp(s,0)), d[s]=0;
		while (!q.empty()) {
			Pair tmp=q.front();
			q.pop_front();
			if (d[tmp.first]!=tmp.second) continue;
			int x=tmp.first;
			ForE(e,x) if (e->f) {
				int y=e->y;
				if (d[x]+e->c<d[y] || d[y]==-1) {
					d[y]=d[x]+e->c;
					prev[y]=e;
					if (q.empty() || d[y]<q.front().second) q.push_front(mp(y,d[y]));
					else q.push_back(mp(y,d[y]));
				}
			}
		}
		if (d[t]==-1) return 0;
		delta=inf;
		for (int x=t; x!=s; x=prev[x]->r->y) delta=min(delta,prev[x]->f);
		for (int x=t; x!=s; x=prev[x]->r->y) prev[x]->f-=delta, prev[x]->r->f+=delta;
		delta*=d[t];
		return 1;
	}
	Pair Run() {
		int ans1=0, ans2=0;
		while (Find())
			ans1++, ans2+=delta;
		return mp(ans1, ans2);
	}
}A;

int main() {
	setIO("test");
	
	n=gi, m=gi;
	int s=0, t=n*2-1;
	A.init(s,t,n*2);
	rep(i,m) {
		int x=gi-1, y=gi-1, c=gi;
		A.Add_Edge(x+n, y, 1, c);
	}
	
	rep(i,n) 
		if (i==0 || i==n-1) A.Add_Edge(i, i+n, inf, 0);
		else A.Add_Edge(i, i+n, 1, 0);
	//return 0;
	Pair ans=A.Run();
	printf("%d %d\n", ans.first, ans.second);
	
	return 0;
}
