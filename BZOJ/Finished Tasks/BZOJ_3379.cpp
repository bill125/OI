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

const int inf=~0U>>1, maxn=1000+10;
int n, m, b;
int dp[maxn][maxn][2];
struct Task {
	int x,t;
	bool operator<(const Task &b) const {
		return x<b.x || (x==b.x && t<b.t);
	}
}A[maxn];

int main() {
	setIO("test");
	
	n=gi, m=gi, b=gi;
	rep(i,n) A[i].x=gi, A[i].t=gi;
	
	sort(A, A+n);
	
	dp[0][n-1][0]=max(A[0].x, A[0].t), dp[0][n-1][1]=max(A[n-1].x, A[n-1].t);
	repD(l,n-1) rep(i,n-l) {
		int j=i+l;
		dp[i][j][0]=dp[i][j][1]=inf;
		if (i) {
			dp[i][j][0]=min(dp[i][j][0], max(A[i].t, dp[i-1][j][0]+A[i].x-A[i-1].x));
			dp[i][j][1]=min(dp[i][j][1], max(A[j].t, dp[i-1][j][0]+A[j].x-A[i-1].x));
		}
		if (j<n-1) {
			dp[i][j][0]=min(dp[i][j][0], max(A[i].t, dp[i][j+1][1]+A[j+1].x-A[i].x));
			dp[i][j][1]=min(dp[i][j][1], max(A[j].t, dp[i][j+1][1]+A[j+1].x-A[j].x));
		}
	}
	int ans=inf;
	rep(i,n) {
		ans=min(ans, min(dp[i][i][0], dp[i][i][1])+abs(A[i].x-b));
	}
	printf("%d\n", ans);
	
	return 0;
}
