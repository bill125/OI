/*
  Task: Substring and Subsequence
  Created: 2012.03.25
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

typedef long long ll;
typedef long double ld; 
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != 0;i = next[i])
#define shl(a,b) (a << b)
#define shr(a,b) (a >> b)
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back

const int maxN = 5000+100,P = 1000000007;
int dp[maxN][maxN],last[maxN][26];
char c1[maxN],c2[maxN];

int getlen(char c[])
{
 	rep(i,maxN) if (c[i] == 0) return i;
}

int main()
{
	scanf("%s\n", c1);scanf("%s\n", c2);
	int N = getlen(c1),M = getlen(c2);
	rep(i,N) rep(j,M) dp[i][j] = 0;
	int ans = 0;
	For(i,1,N) {
      For(j,1,M) {
        dp[i][j] = dp[i][j-1];
        if (c1[i-1] == c2[j-1]) dp[i][j] = (dp[i][j]+dp[i-1][j-1]+1) % P;
 	  } 
 	  ans = (ans + dp[i][M]) % P;
    } 
    printf("%d\n", ans);
	
	return 0;
}
