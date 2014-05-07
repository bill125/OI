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

const int inf=~0U>>1, maxn=200000+10, maxt=600000+10;
int n,m;
ll k,d;

struct SegTree {
	int h;
	struct Node {
		ll L, R, M, sum;
		bool valid;
		Node () { L=R=M=sum=0;valid=0; }
	}a[maxt];
	void init(int n) {
		for (h=1; (1<<h)<n+2; ++h) ;
		For(i,1,n) {
			int x=i+(1<<h);
			a[x].valid=1;
			a[x].L=a[x].R=a[x].M=a[x].sum=-k;
		}
		repD(i,(1<<h)) ref(a[i], a[(i<<1)], a[(i<<1)+1]);
	}
	void ref(Node &t, Node &l, Node &r) { 
		if (!l.valid) { t=r; return ; }
		if (!r.valid) { t=l; return ; }
		t.valid=1;
		t.M=max(max(l.M, r.M), l.R+r.L);
		t.L=max(l.L, l.sum+r.L);
		t.R=max(r.R, r.sum+l.R);
		t.sum=l.sum+r.sum;
	}
	void upd(int x) { for (x>>=1;x;x>>=1) ref(a[x], a[x<<1], a[(x<<1)+1]); }
	void modify(int x,ll t) {
		x+=(1<<h);
		a[x].L+=t, a[x].R+=t, a[x].M+=t, a[x].sum+=t;
		upd(x);
	}
	Node query(int l,int r) {
		l+=(1<<h)-1, r+=(1<<h)+1;
		Node L,R,res;
		while (l+1<r) {
			if (!(l&1)) ref(L, L, a[l^1]);
			if (r&1) ref(R, a[r^1], R);
			l>>=1, r>>=1;
		}
		ref(res, L, R);
		return res;
	}
}T;

int main() {
	setIO("test");
	
	n=gi, m=gi, k=gi, d=gi;
	T.init(n);
	rep(i,m) {
		int x=gi;ll r=gi;
		T.modify(x, r);
		//For(j,0,n+1) printf("%d%c", T.query(j,j).sum, (j==n+1)?'\n':' ');
		//printf("%d\n", T.query(1,n).M);
		if (T.query(1,n).M>k*d) puts("NIE");
		else puts("TAK");
	}
	
	return 0;
}
