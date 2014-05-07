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
int n, MOD=19650827;
int a[maxn];
int dp[maxn][maxn][2];

inline void upd(int &a,int b) {
	if ((a+=b)>=MOD) a-=MOD;
}

int main() {
	setIO("test");
	
	n=gi;
	For(i,1,n) a[i]=gi;
	
	For(i,1,n) dp[i][i][0]=0, dp[i][i][1]=1;
	For(l,2,n) For(i,1,n-l+1) {
		int j=i+l-1;
		if (a[i] < a[i+1]) upd(dp[i][j][0], dp[i+1][j][0]);
		if (a[i] < a[j])   upd(dp[i][j][0], dp[i+1][j][1]);
		if (a[j] > a[i])   upd(dp[i][j][1], dp[i][j-1][0]);
		if (a[j] > a[j-1]) upd(dp[i][j][1], dp[i][j-1][1]);
	}
	printf("%d\n", (dp[1][n][0]+dp[1][n][1])%MOD);
	
	return 0;   
}
