/*
  Task: BZOJ_1049
  Created: 2012.04.16
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != 0;i = next[i])
#define sqr(a) ((a)*(a))
#define shl(a,b) ((a) << (b))
#define shr(a,b) ((a) >> (b))
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define lowbit(x) ((x) & -(x))
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back

const int maxN = 35000+10,INF = 2147483647;
int N,M;
int A[maxN],d[maxN],f[maxN],next[maxN],h[maxN];
ll dp[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int main()
{ 	
	//setIO("test");
	
 	scanf("%d", &N);
 	int k = INF;
 	For(i,1,N) scanf("%d", &A[i]),A[i] -= i,k = min(k,A[i]);
 	if (k <= 0) {
      k = -k+1;
      For(i,1,N) A[i] += k;
    }
    A[0] = 0,A[++N] = INF-10,++N;
 	For(i,1,N) d[i] = INF;
	d[1] = -INF,f[0] = 1;
	For(i,1,N-1) {
      int l = 0,r = i+1;
      while (l + 1 < r) {
	    int mid = (l+r) / 2;
	    if (d[mid] <= A[i]) l = mid;
	    else r = mid;
	  }
	  f[i] = l+1;
      d[f[i]] = min(d[f[i]],A[i]);
	}
    printf("%d\n", N-f[N-1]);
    rep(i,N+1) h[i] = -1,next[i] = -1,dp[i] = -1;
    dp[0] = 0,h[1] = 0;
    For(i,1,N-1) {
      next[i] = h[f[i]];h[f[i]] = i;
      int k = h[f[i]-1];
      while (k != -1) {
        if (A[k] <= A[i]) {
		  ll now = 0;
          For(j,k,i) now += abs(A[j]-A[i]);
          if (dp[i] == -1 || dp[k] + now < dp[i]) dp[i] = dp[k]+now;
          For(j,k,i) {
		    now += abs(A[j]-A[k]) - abs(A[j]-A[i]);
		    if (dp[i] == -1 || dp[k] + now < dp[i]) dp[i] = dp[k]+now;
		  }
        }		 
		k = next[k];
	  }
    }
	printf("%lld\n", dp[N-1]);
	
	return 0;
}
