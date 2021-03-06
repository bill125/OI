/*
  Task:
  Created:
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

const int INF = 2147483647,maxN = 4000+10;
int N,a,b,c;
int f[maxN];

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
 	
 	scanf("%d %d %d %d", &N, &a, &b, &c);
	f[0] = 0;
	For(i,1,N) {
      f[i] = -1;
	  if (i >= a && f[i-a] != -1) f[i] = max(f[i],f[i-a]+1);
	  if (i >= b && f[i-b] != -1) f[i] = max(f[i],f[i-b]+1);
	  if (i >= c && f[i-c] != -1) f[i] = max(f[i],f[i-c]+1);
    }
	printf("%d\n", f[N]);
	
	return 0;
}
