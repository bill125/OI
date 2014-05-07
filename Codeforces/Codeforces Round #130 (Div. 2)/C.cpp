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

const int INF = 2147483647,maxN = 100+10;
int N,M;
bool map[maxN][maxN];
int d[maxN],q[maxN];
ll f[2][maxN];

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
 	
 	scanf("%d %d", &N, &M);
 	fill(map,0);
 	rep(i,M) {
      int a,b;
      scanf("%d %d", &a, &b),--a,--b;
      map[a][b] = map[b][a] = true;
    }
    rep(i,N) d[i] = INF;
    d[0] = q[0] = 0;
    int l = -1, r = 0;
    while (l < r) {
      ++ l;
      rep(i,N) if (map[q[l]][i] && d[i] > d[q[l]] + 1) {
        d[i] = d[q[l]] + 1;
        q[++r] = i;
      }
    }
    rep(i,N) f[0][i] = f[1][i] = 0;
    f[0][0] = 1;
    rep(k,N) {
      int i = q[k];
      rep(j,N) if (d[i] + 1 == d[j] && map[i][j]) f[0][j] += f[0][i];
    }
    f[1][N-1] = 1;
    repD(k,N) {
      int i = q[k];
      rep(j,N) if (d[j] + 1 == d[i] && map[j][i]) f[1][j] += f[1][i];
    }
    db ans = 1;
    For(i,1,N-2) {
      db now = (db) f[0][i] * f[1][i] * 2 / f[0][N-1];
      if (now > ans) ans = now;
    }
    printf("%.8lf\n", ans);
    
	return 0;
}
