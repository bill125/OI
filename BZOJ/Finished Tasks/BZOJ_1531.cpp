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

const int inf=~0U>>1, maxn=200+10, maxc=20000+10;
int n, m;
int b[maxn], c[maxn], q[maxc];
int dp[maxn][maxc];

int main() {
	setIO("test");
	
	n=gi;
	For(i,1,n) b[i]=gi;
	For(i,1,n) c[i]=gi;
	m=gi;
	
	rep(i,n+1) rep(j,m+1) dp[i][j]=inf>>1;
	dp[0][0]=0;
	For(i,1,n) {
		memcpy( dp[i], dp[i-1], sizeof(dp[i]) );
		rep(p,b[i]) {
			int l=0, r=0;
			q[0]=p;
			for (int j=b[i]+p; j<=m; j+=b[i]) {
				if ((j-q[l])/b[i]>c[i]) ++l;
				dp[i][j]=min(dp[i][j], dp[i-1][q[l]]+(j-q[l])/b[i]);
				while (l<=r && dp[i-1][j]<=dp[i-1][q[r]]+(j-q[l])/b[i]) --r;
				q[++r]=j;
			}
		}
	}
	printf("%d\n", dp[n][m]);
	
	return 0;   
}
