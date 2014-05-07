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

const int inf=~0U>>1, maxn=50000+10;
int n;
struct Ground {
	ll w,h;
	bool operator<(const Ground &b) const {
		return (w<b.w || w==b.w && h>b.h);
	}
}a[maxn], b[maxn];
ll dp[maxn];
int q[maxn];

db slope(int j,int k) {
	return (db)(dp[k-1]-dp[j-1])/(a[j].h-a[k].h);
}


int main() {
	setIO("test");
	
	n=gi;
	rep(i,n) a[i].w=gi, a[i].h=gi;
	sort(a,a+n);
	
	int r=1; b[0]=a[0];
	For(i,1,n-1) {
		if (a[i].w==a[i-1].w) continue;
		while (r && b[r-1].h<=a[i].h) --r;
		b[r++]=a[i];
	}
	n=r;
	rep(i,n) a[i+1]=b[i];
	//For(i,1,n) printf("%lld %lld\n", a[i].w, a[i].h);

	dp[0]=0;	
	int l=0;
	r=-1;
	For(i,1,n) {
		while (l<r && slope(q[r-1],q[r])>=slope(q[r],i)) --r;
		q[++r]=i;
		while (l<r && slope(q[l],q[l+1])<=a[i].w) ++l;
		int j=q[l];
		dp[i]=dp[j-1]+a[i].w*a[j].h;
	}
	
	printf("%lld\n", dp[n]);
	
	return 0;
}
