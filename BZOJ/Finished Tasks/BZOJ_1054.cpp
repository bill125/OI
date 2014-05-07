/*
  Task: BZOJ_1054
  Created: 2012.04.19
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
#define ForE(i,a) for (int i = a;i != -1;i = E[i].next)
#define sqr(a) ((a)*(a))
#define shl(a,b) ((a) << (b))
#define shr(a,b) ((a) >> (b))
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define lowbit(x) ((x) & -(x))
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back

const int INF = 2147483647,N = 4,P = 48,MaxM = 70000,dx[4] = {1,0,0,-1},dy[4] = {0,1,-1,0};
int Ans = 0;
int bfs[MaxM],f[MaxM];
struct change
{
 	   int A,B;
}R[P];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int code(int x,int y)
{
 	return (x * N + y);
}

void GetMove()
{
 	 int cnt = -1;
 	 rep(i,N) rep(j,N) rep(k,4) {
       int x = dx[k] + i,y = dy[k] + j;
       if (x >= 0 && x < N && y >= 0 && y < N) {
         ++cnt;
         R[cnt].A = shl(1,code(i,j));R[cnt].B = shl(1,code(x,y));
	   }
	 }
}

int And(int x,int y)
{
 	int k = x&y;
 	return k;
}

int main()
{
 	//setIO("test");
 	
 	char c;
 	GetMove();
 	rep(i,N) {
	  rep(j,N) {
	    c = getchar();
	    if (c == '1') bfs[0] += shl(1,code(i,j));
      }
      scanf("\n");
	}
	scanf("\n");
	rep(i,N) {
	  rep(j,N) {
	    c = getchar();
	    if (c == '1') Ans += shl(1,code(i,j));
      }
      scanf("\n");
	}
	rep(i,70000) f[i] = INF;
	int l = -1,r = 0;
	f[bfs[r]] = 0;
	while (l < r) {
      int k = bfs[++l];
	  rep(i,P) 
        if (And(R[i].A,k) != 0 && And(R[i].B,k) == 0) {
          int j = k-R[i].A + R[i].B;
          if (f[k] + 1 < f[j]) {
            f[j] = f[k] + 1;
            bfs[++r] = j;
            if (j == Ans) break;
		  }
		} 
	  if (bfs[r] == Ans) break;
	}
	printf("%d\n", f[Ans]);
	
	return 0;
}
