/*
  Task: D. Little Elephant and Cards
  Created: 2012.07.12
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

const int INF = 2147483647,maxN = 100000+10,maxC = 200000+10;
int N,C;
struct Color
{
       int w,c;
}A[maxC];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

bool cmp(Color a,Color b)
{
     return (a.c < b.c);
}

int main()
{
 	//setIO("test"); 	
 	
 	scanf("%d", &N);
 	int a,b;
 	rep(i,N) {
      scanf("%d %d", &a, &b);
      A[i*2].w = 1,A[i*2].c = a;
      if (a != b) A[i*2+1].w = 0,A[i*2+1].c = b;
      else A[i*2+1].w = 0,A[i*2+1].c = INF;
    }
    
    A[N*2].w = 0,A[N*2].c = INF;
    C = N*2+1; 
    sort(A,A + C,cmp);
    N = (N+1) /2;
    
    int nowc = 0,nowl = 0,nowt = 0,ans = -1;
    rep(i,C) {
      if (i==0 || A[i].c != nowc) {
        if (nowl >= N) {
          int now = max(N-nowt,0);
          if (now < ans || ans == -1) ans = now;
        }
        nowl = 1,nowc = A[i].c,nowt = A[i].w;
      }
      else ++nowl,nowt += A[i].w;
      if (A[i].c == INF) break;
    }
    
    printf("%d\n", ans);
    
	return 0;
}
