/*
  Task: BZOJ_1072 
  Created: 2012.06.27 
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != -1;i = E[i].next)
#define sqr(a) ((a)*(a))
#define shl(a,b) ((a) << (b))
#define shr(a,b) ((a) >> (b))
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back

const int INF = 2147483647,maxL = 10+10,maxM = shl(1,10)+10,maxd = 1000+10;
int d,L;
int A[maxL],Two[520],dp[maxM][maxd];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int strlen(char c[])
{
    rep(i,maxL) if (c[i] == 0) return i;
}

int lowbit(int x)
{
    return x & -x;
}

int work()
{
    rep(i,shl(1,10)) rep(j,d) dp[i][j] = 0;
    dp[0][0] = 1;
    rep(i,shl(1,L)) rep(j,d) {
      if (dp[i][j] == 0) continue;
      int tmp = (shl(1,L)-1) ^ i,tmp2 = shl(1,10)-1;
      while (tmp != 0) {
        int x = lowbit(tmp),t = A[Two[x]];
        tmp -= x;
        if ((tmp2 & shl(1,t)) == 0) continue;
        tmp2 -= shl(1,t);
        dp[i + x][(j * 10 + t) % d] += dp[i][j];
      }
    }
    return dp[shl(1,L)-1][0];
}

int main()
{
 	//setIO("test");
 	
 	int k = 1;
 	rep(i,10) Two[k] = i,k *= 2;
 	int nT;
 	scanf("%d\n", &nT);
 	while (nT--) {
 	  char c[maxL];
 	  scanf("%s %d\n", c, &d);
 	  L = strlen(c);
 	  rep(i,L) A[i] = c[i] - '0';
      sort(A,A + L);
      printf("%d\n", work());
    }
}
