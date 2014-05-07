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

const int inf=~0U>>1, maxn=12+3, maxM=(1<<12)+10, MOD=100000000;
int n, m;
bool g[maxn][maxn];
int dp[maxn][maxn][maxM];

inline void upd(int &a, int b) {
	a+=b;
	if (a>=MOD) a-=MOD;
}

int main() {
	setIO("test");
	
	m=gi, n=gi;
	rep(i,m) rep(j,n) g[i][j]=gi;
	
	dp[0][0][0]=1;
	rep(i,m) rep(j,n) rep(M,(1<<n)) {
		if (!dp[i][j][M]) continue;
		int ti=(j==n-1)?(i+1):i, tj=(j==n-1)?0:(j+1);
		if (g[i][j]&&!((1<<j)&M)&&(j==0 || !((1<<j-1)&M))) upd( dp[ti][tj][M|(1<<j)], dp[i][j][M] );
		upd( dp[ti][tj][(M&(1<<j))?(M^(1<<j)):M], dp[i][j][M] );
	}
	
	int ans=0;
	rep(M,(1<<n)) upd( ans, dp[m][0][M] );
	printf("%d\n", ans);
	
	return 0;
}
