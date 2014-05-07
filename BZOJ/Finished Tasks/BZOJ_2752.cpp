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
template <typename T> void mine(T &a, const T &b) {if (b<a) a=b;}
template <typename T> void maxe(T &a, const T &b) {if (b>a) a=b;}

const int inf=~0U>>1,maxt=300000+10;
int n,m;

struct Node {
	ll sumL, sumR, sumv, sz, Rv, sumM, add;
	Node () { sumL=sumR=sz=Rv=sumv=sumM=add=0; }
	void addIt(ll k) {
		add+=k;
		sumL+=sz*(sz-1)/2*k;
		sumR+=sz*(sz-1)/2*k;
		sumM+=(sz-1)*sz*(sz+1)*k/6;
		Rv+=k;
		sumv+=(sz-1)*k;
	}
};
Node operator+(Node &l, Node &r) {
	if (l.sz==-1) return r;
	if (r.sz==-1) return l;
	Node t;
	t.sumL=l.sumL+r.sumL+(l.Rv+l.sumv)*r.sz;
	t.sumR=r.sumR+l.sumR+(l.Rv+r.sumv)*l.sz;
	t.sumv=l.sumv+r.sumv+l.Rv;
	t.Rv=r.Rv;
	t.sz=l.sz+r.sz;
	t.sumM=l.sumM+r.sumM+l.sumR*r.sz+l.sz*r.sumL+l.sz*r.sz*l.Rv;
	return t;
}
ll gcd(ll a,ll b) {
	if (a==0) return b;
	return gcd(b%a, a);
}
struct SegTree{
	int h;
	Node a[maxt];
	void init(int n) {
		for (h=1; (1<<h)<n+2; ++h) ;
		rep(i,n) a[i+(1<<h)+1].sz=1;
		repD(i,(1<<h)) ref(i);
	}
	void relax(int x) {
		if (!a[x].add) return ;
		int y=x<<1, z=(x<<1)+1;
		a[y].addIt(a[x].add), a[z].addIt(a[x].add);
		a[x].add=0;
	}
	void ref(int x) { a[x]=a[x<<1]+a[(x<<1)+1]; }
	void pass_down(int x) {	repD(i,(h-1)) relax(x>>(i+1)); }
	void upd(int x) { for (x>>=1; x; x>>=1) ref(x); }
	void add(int x,int y,ll k) {
		int l=x+(1<<h)-1, r=y+(1<<h)+1;
		pass_down(l), pass_down(r);
		while (l+1<r) {
			if (!(l&1)) a[l^1].addIt(k);
			if (r&1) a[r^1].addIt(k);
			l>>=1, r>>=1;
		}
		l=x+(1<<h)-1, r=y+(1<<h)+1;
		upd(l), upd(r);
	}
	Node query(int l,int r) {
		l+=(1<<h)-1, r+=(1<<h)+1;
		pass_down(l), pass_down(r);
		Node L,R;L.sz=R.sz=-1;
		while (l+1<r) {
			if (!(l&1)) L=L+a[l^1];
			if (r&1) R=a[r^1]+R;
			l>>=1, r>>=1;
		}
		return L+R;
	}
}T;

int main() {
	setIO("test");
	
	n=gi, m=gi;
	T.init(n);
	rep(i,m) {
		scanf("\n");
		char style=getchar();
		int l=gi, r=gi;
		if (style=='C') {
			ll k=gi;
			T.add(l,r-1,k);
		}
		else {
			Node t=T.query(l,r);
			ll a=t.sz*(t.sz-1)/2, b=t.sumM;
			ll g=gcd(a,b);
			a/=g, b/=g;
			printf("%lld/%lld\n", b, a);
		}
	}

	
	return 0;
}
