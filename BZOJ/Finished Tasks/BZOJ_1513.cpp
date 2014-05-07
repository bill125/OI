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

const int inf=~0U>>1, maxn=1<<11;
int n, w, h, xl, xr, yl, yr;
ll k;
struct SegTree {
	ll s[maxn], tag[maxn];
	void modify(int, int, int) ;
	void query(int, int, int) ;
};

struct TwoDSegTree {
	SegTree s[maxn], tag[maxn];
	void modify(int, int, int) ;
	void query(int, int, int) ;
}T;

inline void SegTree::modify(int now,int l,int r) {
	s[now]=max(s[now], k);
	if (yl <= l && r <= yr) tag[now]=max(tag[now], k);
	else {
		int m=(l+r)>>1;now<<=1;
		if (yl <= m) modify(now, l, m);
		if (m < yr) modify(now+1, m+1, r);
	}
}

inline void SegTree::query(int now,int l,int r) {
	if (yl <= l && r <= yr) k=max(k, s[now]);
	else {
		k=max(k, tag[now]);
		int m=(l+r)>>1;now<<=1;
		if (yl <= m) query(now, l, m);
		if (m < yr) query(now+1, m+1, r);
	}
}

inline void TwoDSegTree::modify(int now,int l,int r) {
	s[now].modify(1, 0, h);
	if (xl <= l && r <= xr) tag[now].modify(1, 0, h);
	else {
		int m=(l+r)>>1;now<<=1;
		if (xl <= m) modify(now, l, m);
		if (m < xr) modify(now+1, m+1, r);	
	}
}

inline void TwoDSegTree::query(int now,int l,int r) {
	if (xl <= l && r <= xr) s[now].query(1, 0, h);
	else {
		tag[now].query(1, 0, h);
		int m=(l+r)>>1;now<<=1;
		if (xl <= m) query(now, l, m);
		if (m < xr) query(now+1, m+1, r);
	}
}

int main() {
	setIO("test");
	
	w=gi, h=gi, n=gi;

	ll answ=0;
	rep(i,n) {
		int a=gi, b=gi;ll c=gi;
		int x0=gi, y0=gi;
		
		xl=x0, xr=x0+a-1, yl=y0, yr=y0+b-1;
		k=0, T.query(1, 0, w);
		k+=c, T.modify(1, 0, w);
		answ=max(answ, k);
	}
	printf("%I64d\n", answ);
	
	return 0;   
}
