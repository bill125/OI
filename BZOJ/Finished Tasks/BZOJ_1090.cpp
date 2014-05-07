/*
  Task: BZOJ_1090
  Created: 2012.07.02
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

const int INF = 2147483647,maxL = 100+10;
int dp[maxL][maxL],f[maxL][maxL];
char c[maxL];

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

int check(int a,int b)
{
    int l = b-a+1,res = l;
    For(i,1,l/2) if (l % i == 0) {
      bool flag = true;
      For(j,a+i,b) 
        if (c[j] != c[j-i]) {
          flag = false;break;
        }
      if (flag) {
        int now = 2+i+1;
        if (l/i >= 10) ++now;
        if (now < res) res = now;
      }
    }
    return res;
}

int main()
{
 	//setIO("test");
 	
 	scanf("%s", c);
 	int L = strlen(c);
    
    For(p,1,L) rep(i,L-p+1) {
      int j = i+p-1;
      dp[i][j] = p;
      For(k,i,j-1) if (dp[i][k] + dp[k+1][j] < dp[i][j]) dp[i][j] = dp[i][k] + dp[k+1][j];
      For(l,1,p/2) if (p % l == 0) {
        bool flag = true;
        For(k,i+l,j) if (c[k] != c[k-l]) {
          flag = false; break;
        }
        if (!flag) continue;
        int now = dp[i][i+l-1]+2+1;
        if (p / l >= 10) ++now;
        if (now < dp[i][j]) dp[i][j] = now;
      }
    }
    printf("%d\n", dp[0][L-1]);
    
	return 0;
}
