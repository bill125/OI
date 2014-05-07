/*
  Task: BZOJ_1699
  Created: 2012.04.24
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

const int maxN = 1100000,INF = 2147483647;
int N,M,h;
struct Tree
{
 	   int A,B;
}T[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int ask(int l,int r)
{
 	l += shl(1,h)-1,r += shl(1,h)+1;
 	int Max = -INF,Min = INF;
 	while (l + 1 < r) {
      if (l % 2 == 0) Max = max(Max,T[l+1].A),Min = min(Min,T[l+1].B);
      if (r % 2 == 1) Max = max(Max,T[r-1].A),Min = min(Min,T[r-1].B);
      l /= 2;r /= 2;
	}
	return (Max-Min);
}

int main()
{
 	//setIO("test");
 	
 	scanf("%d %d", &N, &M);
    h = 1;
    while (shl(1,h) < N+2) ++h;
    int k;
    rep(i,N) scanf("%d", &k),T[shl(1,h)+i+1].A = T[shl(1,h)+i+1].B = k;
	ForD(i,shl(1,h)-1,1) {
      T[i].A = max(T[i*2].A,T[i*2+1].A);
      T[i].B = min(T[i*2].B,T[i*2+1].B);
    }
    rep(i,M) {
      int a,b;
      scanf("%d %d", &a, &b);
      printf("%d\n", ask(a,b));
	}
	
	return 0;
}
