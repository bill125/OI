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
#define ForE(i,a) for (Edge* i=h[a]; i; i=i.next)
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

const int inf=~0U>>1, maxt=300000+10;
int n;
char c[30];

struct Node {
	bool valid;
	bool f[2][2];
	bool L, R;
	bool v[2];
	Node () { fill(f,0), v[0]=v[1]=L=R=valid=0; }
};
Node operator+(Node &l, Node &r) {
	if (!l.valid) return r;
	if (!r.valid) return l;
	Node t;t.valid=1;
	rep(i,2) rep(j,2) rep(x,2) 
		if (l.f[i][x] && r.f[x][j] && l.v[x])
			t.f[i][j]=1;
	t.v[0]=r.v[0], t.v[1]=r.v[1];
	t.L=l.L || (r.L && l.f[0][0] && l.f[1][1] && l.v[0] && l.v[1]);
	t.R=r.R || (l.R && r.f[0][0] && r.f[1][1] && l.v[0] && l.v[1]);
	return t;
}

struct SegTree {
	Node a[maxt];
	int h;
	void init(int n) {
		for (h=1; (1<<h)<n+2; ++h) ;
		rep(i,n) {
			Node &t=a[i+(1<<h)+1];
			t.f[0][0]=t.f[1][1]=t.valid=1;
		}
		repD(i,(1<<h)) ref(i);
	}
	void ref(int x) { a[x]=a[x<<1]+a[(x<<1)+1]; }
	void upd(int x) { for (x>>=1; x; x>>=1) ref(x); }
	Node query(int l,int r) {
		l+=(1<<h)-1, r+=(1<<h)+1;
		Node L,R;
		while (l+1<r) {
			if (!(l&1)) L=L+a[l^1];
			if (r&1) R=a[r^1]+R;
			l>>=1, r>>=1;
		}
		return L+R;
	}
	void chg1(int x,bool flag) {
		x+=(1<<h);
		a[x].f[0][1]=a[x].f[1][0]=flag;
		a[x].L=a[x].R=flag;
		upd(x);
	}
	void chg2(int x,int y,bool flag) {
		x+=(1<<h);
		a[x].v[y]=flag;
		upd(x);
	}
}T;

int main() {
	setIO("test");
	
	n=gi;
	T.init(n);

	while (scanf("%s", c)) {
		if (c[0]=='E') return 0;
		int r1=gi-1, c1=gi, r2=gi-1, c2=gi;
		if (c1>c2) swap(r1, r2), swap(c1, c2);
		if (c[0]=='O') {
			if (c1==c2) T.chg1(c1,1);
			else T.chg2(c1,r1,1);
				
		}
		else if (c[0]=='C') {
			if (c1==c2) T.chg1(c1,0);
			else T.chg2(c1,r1,0);
		}
		else if (c[0]=='A') {
			Node l=T.query(1,c1), r=T.query(c2,n), m=T.query(c1,c2);
			if (l.R) rep(i,2) if (m.f[0][i] || m.f[1][i]) m.f[0][i]=m.f[1][i]=1;
			if (r.L) rep(i,2) if (m.f[i][0] || m.f[i][1]) m.f[i][0]=m.f[i][1]=1;
			if (m.f[r1][r2]) puts("Y");
			else puts("N");
		}
	}
	
	return 0;
}
