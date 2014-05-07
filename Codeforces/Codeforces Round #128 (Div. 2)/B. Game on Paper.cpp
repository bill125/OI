/*
  Task: B. Game on Paper
  Created: 2012.07.03
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

const int INF = 2147483647,maxN = 1000+10;
int N,M;
bool map[maxN][maxN],flag = false;

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
 	rep(i,N) rep(j,N) map[i][j] = false;
 	rep(t,M) {
      int x,y;
      scanf("%d %d", &x, &y),--x,--y;
      map[x][y] = true;
      int MinX = max(x-2,0),MaxX = min(x+2,N-1);
      int MinY = max(y-2,0),MaxY = min(y+2,N-1);
      int nowL = MinY,nowR = MaxY;
      int cnt = 0;
      For(i,MinX,MaxX) { 
        int L = MinY,R = -1;
        For(j,MinY,MaxY) 
          if (map[i][j]) R = j;
          else if (R-L+1 >= 3) break;
          else L = j+1;
        nowL = max(nowL,L),nowR = min(nowR,R);
        if (nowR - nowL + 1 < 3) cnt = 0,nowL = MinY,nowR = MaxY;
        else ++cnt;
        if (cnt >= 3) {
          flag = true; break;
        }
      }
      if (flag) {
        printf("%d\n", t+1);
        break;
      }
    }
    if (!flag) printf("-1\n");
    
	return 0;
}
