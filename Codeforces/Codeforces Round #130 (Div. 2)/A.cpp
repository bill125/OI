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

const int INF = 2147483647,maxN = 200+10;
int N;
char c[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int strlen(char c[])
{
    rep(i,maxN) if (c[i] == 0) return i;
}

int main()
{
 	//setIO("test"); 	
 	
 	scanf("%s", c);
 	N = strlen(c);
 	int H = 0,T = N-1;
 	while (H+2 < T && c[H] == 'W' && c[H+1] == 'U' && c[H+2] == 'B') H += 3;
 	while (H+2 < T && c[T-2] == 'W' && c[T-1] == 'U' && c[T] == 'B') T -= 3;
 	int i = H;
 	while (true) {
      if (i <= T-2 && c[i] == 'W' && c[i+1] == 'U' && c[i+2] == 'B') {
        while (i <= T-2 && c[i] == 'W' && c[i+1] == 'U' && c[i+2] == 'B') i += 3;
        printf(" ");
      }
      else printf("%c", c[i]),++i; 
      if (i == T+1) {printf("\n");return 0;}
    }
    
	return 0;
}
