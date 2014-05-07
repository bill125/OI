/*
  Task: BZOJ_1010
  Created: 2012.02.27
  Author: Zhu Jiahao
*/

#include<cstdio>

using namespace std;

#define For(i,a,b) for (i = a;i <= b;++i)
#define rep(i,n) for (i = 0;i < n;++i)

const int maxN = 50000+10;
const double INF = 1e100;
long long i,l,r,N,L,C;
long long dp[maxN],sub[maxN],B[maxN];
int q[maxN];

long long sqr(long long x)
{
    return x*x;
}

double slope(int a,int b)
{
     if (B[a] == B[b]) {
       if (dp[a] >= dp[b]) return -INF;
       else return INF;
	 }
	 return ((dp[a]-dp[b]+sqr(B[a])-sqr(B[b]))/(B[a]-B[b]));
}

int main()
{    
    scanf("%d %d", &N, &L);
    sub[-1] = 0;B[-1] = L + 1;
	rep(i,N) {
      scanf("%d", &C);
      sub[i] = sub[i-1] + C + 1;
      B[i] = sub[i] + L + 1;
    }
    l = 0,r = 0,q[0] = -1,dp[-1] = 0;
    rep(i,N) {
      while (l < r && slope(q[l],q[l+1]) < sub[i]*2) ++l;
      dp[i] = dp[q[l]] + sqr(sub[i] - B[q[l]]);
      while (l < r && slope(q[r-1],q[r]) > slope(q[r],i)) --r;
      q[++r] = i;
    }
    printf("%lld\n", dp[N-1]);
    
    return 0;
}
