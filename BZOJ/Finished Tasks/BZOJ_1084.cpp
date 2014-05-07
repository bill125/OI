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

const int INF = 2147483647,maxN = 100+10,maxM = 3+10,maxK = 10+10;
int N,M,K;
int A[maxN][maxM],f[maxN][maxK][maxM]; 

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
 	
 	scanf("%d %d %d", &N, &M, &K);
 	if (M == 1) {
      For(i,1,N) scanf("%d", &A[i][0]);
      rep(i,N+1) rep(j,K+1) f[i][j][0] = f[i][j][1] = -INF/2;
      rep(i,N+1) f[i][0][0] = 0;
      For(i,1,N) For(j,1,K) {
        f[i][j][0] = max(f[i-1][j][0],f[i-1][j][1]);
        f[i][j][1] = max(f[i-1][j][1],f[i-1][j-1][0])+A[i][0];
      }
      printf("%d\n", max(f[N][K][0],f[N][K][1]));
    }
    else {
      For(i,1,N) rep(j,M) scanf("%d", &A[i][j]);
      rep(i,N+1) rep(j,K+1) f[i][j][0] = f[i][j][1] = f[i][j][2] = f[i][j][3] = f[i][j][4] = f[i][j][5] = -INF/2;
      rep(i,N+1) f[i][0][0] = f[i][0][5] = 0;
      For(i,1,N) For(j,1,K) {
        f[i][j][0] = f[i-1][j][5];
        f[i][j][1] = max(max(f[i-1][j][1],f[i-1][j][4]),f[i-1][j-1][5])+A[i][0];
        f[i][j][2] = max(max(f[i-1][j][2],f[i-1][j][4]),f[i-1][j-1][5])+A[i][1];
        f[i][j][3] = max(f[i-1][j][3],f[i-1][j-1][5])+A[i][0]+A[i][1];
        if (j > 1) f[i][j][4] = f[i-1][j-2][5];
        f[i][j][4] = max(max(f[i-1][j-1][1],f[i-1][j-1][2]),max(f[i][j][4],f[i-1][j][4]))+A[i][0]+A[i][1];
        f[i][j][5] = max(f[i][j][0],max(max(f[i][j][1],f[i][j][2]),max(f[i][j][3],f[i][j][4])));
      }   
      printf("%d\n", f[N][K][5]); 
    } 
    
	return 0;
}
