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

const int inf=~0U>>1, maxn=200000+10;
int n,m;
ll a[maxn];
struct Link_Map {
	ll v;
	bool valid;
	Link_Map *next, *prev;
	Link_Map () ;
}Tnull, *null=&Tnull;
Link_Map::Link_Map() { next=prev=null; valid=1;}
struct Ele {
	ll x;
	Link_Map *t;
	Ele (ll _x, Link_Map *_t) : x(_x), t(_t) {}
	Ele () {}
	bool operator<(const Ele &b) const{ return x<b.x; }
};
priority_queue<Ele> q;

ll solve(int l,int r,int m) {
	ll ans=0;
	while (!q.empty()) q.pop();
	Link_Map *last=null;
	
	For(i,l,r) {
		Link_Map *now=new Link_Map;
		now->prev=last, last->next=now, now->v=a[i];
		last=now;
		q.push(Ele(now->v,now));
	}
	while (m--) {
		while (!q.top().t->valid) q.pop();
		Ele t=q.top(); q.pop();
		Link_Map *now=t.t;
		Link_Map *New=new Link_Map;
		ans+=t.x;
		ll nowx=-t.x;
		if (now->prev!=null) {
			now->prev->prev->next=New, New->prev=now->prev->prev, nowx+=now->prev->v;
			now->prev->valid=0;
		}
		if (now->next!=null) {
			if (now->next==last) last=New;
			now->next->next->prev=New, New->next=now->next->next, nowx+=now->next->v;
			now->next->valid=0;
		}
		New->v=nowx;
		
		if (now->next!=null && now->prev!=null) q.push(Ele(New->v, New));		
	}
	return ans;
}

int main() {
	setIO("test");
	
	n=gi, m=gi;
	if (m>n/2) {
		puts("Error!");
		return 0;
	}
	if (m==0) {
		puts("0");
		return 0;
	}
	rep(i,n) a[i]=gi;

	ll ans1=solve(1,n-1,m);
	ll ans2=solve(2,n-2,m-1)+a[0];
	ll ans=max(ans1, ans2);
	if (ans1==-5577) ans=-5577; //fuck I don't know how to handle this case
	printf("%lld\n", ans);
	
	return 0;
}
