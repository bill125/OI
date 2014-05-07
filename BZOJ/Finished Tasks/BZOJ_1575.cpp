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

const int maxn=100+10;
const ll inf=1000000000000000LL;
int n,e;
ll s0[maxn][maxn], a[maxn];
ll dp[maxn][maxn];

int main() {
	setIO("test");
	
	n=gi, e=gi;
	For(i,1,n) a[i]=gi;
	
	For(i,1,n) For(j,1,n) dp[i][j]=inf;
	For(i,1,n) {
		dp[i][1]=0;
		For(j,1,i-1) dp[i][1]+=2*abs(a[j]-a[i]);
	}
	
	For(i,1,n) For(j,i+1,n) {
		s0[i][j]=0;
		For(k,i+1,j-1) s0[i][j]+=abs(2*a[k]-a[i]-a[j]);
	}
	
	For(i,1,n) For(j,2,i) {
		For(k,1,i-1) dp[i][j]=min(dp[i][j],dp[k][j-1]+s0[k][i]); 
	}
	ll ans=inf, anse;
	For(i,1,n) {
		ll t=0;
		For(j,i+1,n) t+=2*abs(a[j]-a[i]);
		For(j,1,i) {
			dp[i][j]+=t;
			if (dp[i][j]<=e) 
				if (j<ans) ans=j, anse=dp[i][j];
				else if (j==ans && dp[i][j]<anse) anse=dp[i][j];
		}
	}
	printf("%lld %lld\n", ans, anse);
	
	return 0;
}
