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

const int inf=~0U>>1,maxn=10000+10,MOD=1000000009;
int n,m;
ll a[maxn];
int num[maxn];

bool cmp(int x,int y) {
	return (a[x] < a[y] || (a[x]==a[y] && y<x));
}

inline void update(ll &x,const ll &y) {
	x+=y;
	if (x>=MOD) x-=MOD;
	if (x<0) x+=MOD;
}

struct TreeArr {
	int n;
	ll a[maxn];
	void init(int _n) {
		n=_n;
		fill(a,0);
	}
	void Add(int x,int y) {
		for (; x<=n; x+=lowbit(x)) 
			update(a[x],y);
	}
	ll Sum(int x) {
		ll res=0;
		for (; x; x-=lowbit(x)) 
			update(res,a[x]);
		return res;
	}
}A,B,C;

int main() {
	setIO("test");
	
	n=gi, m=gi;
	vector<ll> tmp(m, 0);
	vector<vector<ll> > f(n, tmp),L(n, tmp),R(n, tmp),U(n, tmp),D(n, tmp);
	
	for (int q=gi; q--; ) {
		int x=gi-1, y=gi-1;
		f[x][y]=1;
	}
	
	rep(i,n) {
		rep(j,m) 
			if (f[i][j]==1) L[i][j]=0;
			else L[i][j]=(j==0)?1:L[i][j-1]+1;
		repD(j,m)
			if (f[i][j]==1) R[i][j]=0;
			else R[i][j]=(j==m-1)?1:R[i][j+1]+1;
	}
	
	rep(j,m) {
		rep(i,n) 
			if (f[i][j]==1) U[i][j]=0;
			else U[i][j]=(i==0)?1:U[i-1][j]+1;
		repD(i,n)
			if (f[i][j]==1) D[i][j]=0;
			else D[i][j]=(i==n-1)?1:D[i+1][j]+1;
	}

	ll ans=0;
	rep(j,m) {
		A.init(n),B.init(n),C.init(n);
		rep(i,n) {
			a[i]=min(L[i][j],R[i][j])-1;
			num[i]=i;
			A.Add(i+1,U[i][j]-1);
		}
		sort(num, num+n, cmp);
		rep(k,n) {
			int i=num[k];
			if (i==0) continue;
			if (U[i][j]>=4) {
				ll now=0;
				now+=B.Sum(i-1)-B.Sum(i-U[i][j]+1);
				now+=(C.Sum(i-1)-C.Sum(i-U[i][j]+1))*a[i];
				now+=(A.Sum(i-1)-A.Sum(i-U[i][j]+1))*(a[i]-1)*a[i]/2;
				now%=MOD;
				now=(now*(D[i][j]-1))%MOD;
			
				update(ans,now);
			}
			A.Add(i+1,1-U[i][j]);
			B.Add(i+1,(-a[i]*a[i]-a[i])*(U[i][j]-1)/2);
			C.Add(i+1,a[i]*(U[i][j]-1));
		}
	}
	printf("%lld\n", ans);
	
	return 0;
}
