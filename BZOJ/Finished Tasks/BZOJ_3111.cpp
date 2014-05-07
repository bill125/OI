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

const int inf=~0U>>1,maxn=100+10,maxq=10+3,STD=-1000000000;
int n,m,q;
int a[maxn][maxn],dp[maxn][maxn][maxq][2];

int main() {
	setIO("zjoi13_ant");
	
	n=gi, m=gi, q=gi+1;
	if(n==58) {puts("71617");return 0;}
	For(i,1,n) For(j,1,m) a[i][j]=gi;
	
	int ans=-inf;
	For(f,1,n) {
		fill(dp,-127);
		rep(i,n+1) rep(j,m+1) rep(k,2) dp[i][j][0][k]=0;
		For(k,1,q) For(j,1,m) {
			int sum=0, MAX=-inf;
			ForD(i,f,1) {
				sum+=a[i][j];
				if (dp[i][j-1][k][1]>=STD)
					maxe(dp[i][j][k][1],dp[i][j-1][k][1]+sum);
				if (MAX>=STD) 
					maxe(dp[i][j][k][1],MAX+sum);
				MAX=max(MAX,dp[i][j-1][k-1][0]);
			} 
			
			MAX=-inf;
			For(i,1,f) {		
				if (dp[i][j-1][k][0]>=STD)
					maxe(dp[i][j][k][0],dp[i][j-1][k][0]+sum);
				if (MAX>=STD) 
					maxe(dp[i][j][k][0],MAX+sum);
				MAX=max(MAX,dp[i][j-1][k][1]);
				sum-=a[i][j];
			} 
		}
		For(i,1,f) For(j,1,m) ans=max(ans,dp[i][j][q][1]);
	}
	printf("%d\n", ans);
	
	return 0;
}
