/*
  Task: E. Wooden Fence
  Created: 2012.04.25
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

const int maxN = 200+10,maxNum = 100+10,maxL = 3000+10,P = 1000000007,INF = 2147483647;
int N,L;
int f[maxL][maxN];
struct fence
{
 	   int A,B,Num;
}F[maxN];

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
 	
 	scanf("%d %d", &N, &L);
 	fill(f,0);
	int a,b;
	int cnt = -1;
	rep(i,N) {
      scanf("%d %d", &a, &b),
      ++cnt;
      F[cnt].A = a;F[cnt].B = b;F[cnt].Num = i;
      if (a != b) {
        ++cnt;
		F[cnt].A = b;F[cnt].B = a;F[cnt].Num = i;
      }
	}
	N = cnt + 1;
	rep(i,N) f[F[i].A][i] = 1;
    For(i,1,L) 
      rep(j,N) rep(k,N) 
	    if (F[j].Num != F[k].Num && F[k].A < i && F[j].B == F[k].A) f[i][k] = (f[i][k]+f[i-F[k].A][j])%P;
    int ans = 0;
	rep(i,N) ans = (ans + f[L][i]) % P;
	printf("%d\n", ans);
	
	return 0;
}
