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

const int inf=~0U>>1, maxm=100000+10, maxp=300000+10;
int n, m, K;
int num[maxm], ans[maxm], id[maxm];
int Left[maxm], Right[maxm];
int dp[maxm];
struct Quest {
	int l, r;
	bool operator<(const Quest &b) const { return l<b.l || l==b.l && r>b.r; }
	bool operator==(const Quest &b) const { return l==b.l &&r==b.r; }
}A[maxm], B[maxm];

struct node {
	int a, sz, cov;
	node () { a=cov=0, sz=-1; }
	void covIt() {
		if (sz==-1) return;
		cov=a=1;
	}
}t;
node operator+(node &l, node &r) {
	if (l.sz==-1) { t=r; t.cov=0; return t; }
	if (r.sz==-1) { t=l; t.cov=0; return t; }
	t.sz=l.sz+r.sz;t.cov=0;
	return t;
}
struct segment_tree {
	node a[maxp];
	int h;
	void relax(int x) {
		if (a[x].cov) {
			a[x<<1].covIt(); a[(x<<1)+1].covIt();
			a[x].cov=0;
		}
	}
	void ref(int x) { a[x]=a[x<<1]+a[(x<<1)+1]; }
	void pass(int x) { repD(i,h-1) relax(x>>i+1); }
	void init(int n) {
		for (h=1; (1<<h)<n+2; ++h) ;
		rep(i,n) a[i+(1<<h)+1].sz=1;
		repD(i,(1<<h)) ref(i);
	}
	void cover(int x,int y) {
		int l=x+(1<<h)-1, r=y+(1<<h)+1;
		pass(l), pass(r);
		while (l+1 < r) {
			if (!(l&1)) a[l^1].covIt();
			if (r&1) a[r^1].covIt();
			l>>=1, r>>=1;
		}
	}
	int query(int x) {
		x+=(1<<h);
		pass(x);
		return a[x].a;
	}
}T;

int main() {
	setIO("test");
	
	n=gi, K=gi, m=gi;
	int _m=0;
	T.init(n);
	rep(i,m) {
		int l=gi, r=gi, k=gi;
		if (!k) T.cover(l, r);
		else {
			A[_m].l=l-1, A[_m].r=r-1;
			++_m;
		}
	}
	
	int tag=0;
	fill(num, -1);
	rep(i,n) if (!T.query(i+1)) num[i]=tag, id[tag]=i, ++tag;
	
	
	if (K==tag) {
		rep(i,tag) printf("%d\n", id[i]+1);
		return 0;
	}
	
	Left[0]=num[0], Right[n-1]=num[n-1];
	For(i,1,n-1)  Left[i]=(num[i]!=-1)?num[i]:Left[i-1];
	ForD(i,n-2,0) Right[i]=(num[i]!=-1)?num[i]:Right[i+1];
	
	m=_m;
	
	rep(i,m) A[i].l=Right[A[i].l], A[i].r=Left[A[i].r];
	
	sort(A, A+m);
	
	_m=1;
	For(i,1,m-1) if (!(A[i]==A[i-1])) A[_m++]=A[i];
	
	m=_m; _m=0;
	
	
	int ansl=0, LeftMost=tag;
	repD(i,m) {
		if (A[i].l == A[i].r) ans[ansl++]=id[A[i].l];
		else if (A[i].r < LeftMost) B[_m++]=A[i];
		LeftMost=min(LeftMost, A[i].r);
	}
	m=_m;
	
	rep(i,m) A[i]=B[_m-1-i];
	//rep(i,m) printf("%d %d\n", A[i].l, A[i].r);
	
	int last=1000000000;
	repD(i,m) {
		dp[i]=(i==m-1)?0:dp[i+1];
		if (last > A[i].r) {
			last = A[i].l;
			++dp[i];
		}
	}
	
	last=-1;int cnt=ansl;
	rep(i,m) 
		if (last < A[i].l) {
			last=A[i].r, ++cnt;
			int l=i, r=m;
			while (l+1 < r) {
				int m=l+r >> 1;
				if (A[m].l >= A[i].r) r=m;
				else l=m;
			}
			int t = (r!=m)?dp[r]:0; 
			if (cnt + t > K) ans[ansl++]=id[A[i].r];
		}
	
	sort(ans, ans+ansl);
	rep(i,ansl) printf("%d\n", ans[i]+1);
	
	return 0;   
}
