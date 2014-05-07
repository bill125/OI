//Author: bill125

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
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)>(b))?(b):(a))
#define pb push_back
#define mp make_pair
#define v1 first
#define v2 second
#define gi gI()
#define cut puts("===================")

void setIO(string NAME) {
	#ifndef ONLINE_JUDGE
	string in = NAME + ".in";
	string out = NAME + ".out";
	freopen(in.c_str(),"r",stdin);
	freopen(out.c_str(),"w",stdout);
	#endif
}
ll gI() {
	char c=getchar();
	while ((c<'0' || c>'9')&&c!='-') c=getchar();
	ll flag=1,p=0;
	if (c=='-') flag=-1,c=getchar();
	while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();
	return p*flag;
}
int gs(char *C) {
	char c=getchar();
	while (c==' ' || c=='\n') c=getchar();
	int l=0;
	while (c!=' ' && c!='\n') C[l++]=c,c=getchar();
	C[l]=0;
	return l;
}

template <class T> void debug (const T a,const int & n) {rep(i,n) printf("%d%c", a[i], (i==n-1) ? '\n' : ' ');}
template <typename T> void mine(T &a, const T &b) {if (b<a) a=b;}
template <typename T> void maxe(T &a, const T &b) {if (b>a) a=b;}

const int inf=~0U>>1, maxn=100000+10, maxl=300000+10;
int n,m;
int a[maxn];

struct Seg {
	int chg, L, R;
	ll sum;
	Seg () {chg=0;}
	Seg *l, *r;
	void upd() {
		sum=l->sum+r->sum;
		chg=l->chg+r->chg;
		L=l->L, R=r->R;
	}
}*root;

Seg *build(int L,int R,int a[]) {
	if (L+1==R) {
		Seg *now=new Seg;
		now->chg=5, now->sum=a[L];
		now->L=L, now->R=R;
		return now;
	}
	int M=(L+R)>>1;
	Seg *now=new Seg;
	now->l=build(L,M,a);
	now->r=build(M,R,a);
	now->upd();
	return now;
}
void modify(int L,int R,Seg *now) {
	if (!now->chg) return ;
	if (now->L+1==now->R) {
		now->chg--;
		now->sum=(int)sqrt(now->sum);
		return ;
	}
	if (now->l->R>L) modify(L,R,now->l);
	if (now->r->L<R) modify(L,R,now->r);
	now->upd();
}
ll query(int L,int R,Seg *now) {
	if (L<=now->L&&now->R<=R) 
		return now->sum;
	ll res=0;
	if (now->l->R>L) res+=query(L,R,now->l);
	if (now->r->L<R) res+=query(L,R,now->r);
	return res; 
}

int main() {
	setIO("test");
	
	n=gi;
	rep(i,n) a[i]=gi;
	m=gi;
	root=build(0,n,a);

	rep(i,m) {
		int style=gi, l=gi-1, r=gi;
		if (style==1) printf("%lld\n", query(l,r,root));
		else modify(l,r,root);
	}
	
	return 0;
}
