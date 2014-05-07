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

const int inf=~0U>>1, maxn=600+10, maxm=50+10;
int n,m;
int a[maxn][maxn], sum[maxn][maxn], g[maxn][maxn], dp[maxn][maxm], prev[maxn][maxm];
int ansq[maxn];

int main() {
	setIO("test");
	
	n=gi, m=gi;
	For(i,1,n) For(j,i+1,n) a[i][j]=gi;
	For(i,1,n) ForD(j,n,i) sum[i][j]=sum[i][j+1]+a[i][j];
	ForD(i,n,1) For(j,i+1,n) g[i][j]=g[i+1][j]+sum[i][j];
	
	int ans=0, ansi;
	fill(dp,-1);
	dp[0][0]=0;
	For(i,1,n) For(j,1,m) {
		For(k,0,i-1) 
			if (dp[k][j-1]+g[k+1][i+1] > dp[i][j]) {
				dp[i][j]=dp[k][j-1]+g[k+1][i+1]; 
				prev[i][j]=k;
			}
		if (dp[i][m]>ans) {
			ans=dp[i][m];
			ansi=i;
		}
	}
	
	int k=m, r=0;
	for (;ansi!=0;ansi=prev[ansi][k--]) ansq[r++]=ansi;
	repD(i,r) printf("%d%c", ansq[i], (i==0)?'\n':' ');
	
	return 0;
}
