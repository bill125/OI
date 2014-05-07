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

const int inf=~0U>>1, maxn=500000+10;
int n;
int s[maxn];
ll a[maxn];
db ans1[maxn], ans2[maxn];
db sqt[maxn];

inline db Status(db i,int j) {
	return (db)a[j]+sqrt((db)abs(i-j));
}
int Time(int i,int j) {
	int l=j, r=n+1;
	while (l < r) {
		int m=(l+r)/2;
		if (a[i]+sqt[abs(i-m)] >= a[j]+sqt[abs(j-m)]) l=m+1;
		else r=m;
	}
	return l;
}

void solve (db ans[], ll a[]) {
	fill(ans, 0);
	int l=0, r=0;
	
	rep(i,n) {
		while (l<r && Status(i, s[l]) < Status(i, s[l+1])) ++l;
		ans[i]=max(ans[i], (Status(i, s[l]))-a[i]);
		
		while (l<r && Time(s[r-1], s[r]) > Time(s[r], i)) --r;
		s[++r]=i;
	}
}

int main() {
	setIO("test");
	
	n=gi;
	rep(i,n) a[i]=gi;
	
	For(i,0,n) sqt[i]=sqrt((db)i);
	
	solve(ans1, a);
	rep(i,n/2) swap(a[i], a[n-i-1]);
	solve(ans2, a);
	rep(i,n/2) swap(ans2[i], ans2[n-i-1]);
	
	rep(i,n) {
		db ans=max(ans1[i], ans2[i]);
		printf("%lld\n", (ll) ceil(ans));
	}
		
	return 0;
}
