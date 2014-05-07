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

const int inf=~0U>>1,maxt=5000000,maxm=300000+10;
int w,m=0;
ll ans[maxm];
bool v[maxm];
struct Node {
	ll sum;
	bool valid, clr;
	void clrIt() { sum=0, clr=1; }
	Node () { sum=valid=clr=0; }
};
Node operator+(Node &l, Node &r) {
	Node t;
	if (!l.valid) { t=r; t.clr=0; return t; }
	if (!r.valid) { t=l; t.clr=0; return t; }
	
	t.sum=l.sum+r.sum;
	t.valid=1;
	return t;
}
struct SegTree {
	int h;
	Node a[maxt];
	void init(int n) {
		for (h=1; (1<<h)<n+2; ++h) ;
		rep(i,n) {
			Node &t=a[i+(1<<h)+1];
			t.valid=1, t.sum=0;
		}
		repD(i,(1<<h)) ref(i);
	}
	void ref(int x) { a[x]=a[x<<1]+a[(x<<1)+1]; }
	void upd(int x) { for (x>>=1; x; x>>=1) ref(x); }
	void relax(int x) { 
		if (!a[x].clr) return;
		int y=x<<1, z=y+1;
		if (x<=(1<<h)) a[y].clrIt(), a[z].clrIt();
		a[x].clr=0;
	}
	void pass_down(int x) {	repD(i,h) relax(x>>(i+1)); }
	void add(int x,ll k) {
		x+=(1<<h);
		pass_down(x);
		a[x].sum+=k;
		upd(x);
	}
	Node query(int l,int r) {
		l+=(1<<h)-1, r+=(1<<h)+1;
		pass_down(l), pass_down(r);
		Node L,R;L.valid=R.valid=0;
		while (l+1<r) {
			if (!(l&1)) L=L+a[l^1];
			if (r&1) R=a[r^1]+R;	
			l>>=1, r>>=1;
		}
		return L+R;
	}
	void clear() { a[1].clrIt(); }
}T;
struct Opr {
	int x,y,l,r,i,style;
	ll k,p;
	bool operator<(const Opr& b) {
		return y<b.y||y==b.y&&style<b.style;
	}
}a[maxm], b[maxm];

void work(int l,int r) {
	if (l==r) return;
	int m=(l+r)>>1;
	work(l,m), work(m+1,r);
	T.clear();
	
	int i=l, j=m+1;
	For(k,l,r) 
		if (j>r || (i<=m && a[i]<a[j])) b[k]=a[i++], v[k]=1;
		else b[k]=a[j++], v[k]=0;
	For(i,l,r) {
		a[i]=b[i];
		if (a[i].style==1 && v[i]) {
			T.add(a[i].x, a[i].k);

		}
		if (a[i].style==2 && !v[i]) a[i].k+=T.query(a[i].l, a[i].r).sum;
	}
}

int main() {
	setIO("test");
	
	ll t=gi; w=gi;
	T.init(w);
	int style,tot=0;
	while ((style=gi)!=3) {
		if (style==1) {
			int x=gi, y=gi; ll k=gi;
			a[m].x=x, a[m].y=y, a[m].k=k, a[m].style=1;++m;
		}
		else {
			ll x1=gi, y1=gi, x2=gi, y2=gi;
			if (x1>x2) swap(x1,x2);
			if (y1>y2) swap(y1,y2);
			a[m].l=x1, a[m].r=x2, a[m].y=y1-1, a[m].p=-1, a[m].style=2, a[m].i=tot;++m;
			a[m].l=x1, a[m].r=x2, a[m].y=y2, a[m].p=1, a[m].style=2, a[m].i=tot;++m;
			ans[tot]=(y2-y1+1)*(x2-x1+1)*t;
			++tot;
		}
	}
	
	work(0,m-1);
	
	rep(i,m) ans[a[i].i]+=a[i].k*a[i].p;
	rep(i,tot) printf("%lld\n", ans[i]);
	
	return 0;
}
