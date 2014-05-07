/*
  Task: BZOJ_1305
  Created: 2012.04.26
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

const int maxN = 50+10,maxP = 200+10,INF = 2147483647;
int N,K,S,T,delta;
int cA[maxN],cB[maxN],f[maxP][maxP],q[maxP],d[maxP];
char c;
bool v[maxP],map[maxN][maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

bool Build()
{
 	 int l = -1,r = 0;
 	 rep(i,T+1) d[i] = INF;
 	 fill(v,0);
 	 q[0] = S,v[S] = true,d[S] = 0;
 	 while (l < r) {
       int k = q[++l];
       rep(i,T+1) 
         if (f[k][i] && d[k] + 1 < d[i]) {
           d[i] = d[k]+1;
		   if (!v[i]) {
		     q[++r] = i;v[i] = true;
		     if (i == T) return true;
		   }
		 }  
       v[k] = false;
	 }
	 return false;
}

bool Find(int x,int now_flow)
{
 	 if (x == T) {
       delta = now_flow;
       return true;
	 }
	 rep(i,T+1) 
       if (f[x][i] && d[x] + 1 == d[i] && Find(i,min(now_flow,f[x][i]))) {
         f[x][i] -= delta;f[i][x] += delta;
         return true;
	   }
     return false;
}

bool check(int x)
{
 	 fill(f,0);
 	 S = 0,T = N*4+1;
 	 rep(i,N) f[S][i+1] = x,f[i+N*2+1][T] = x;
 	 rep(i,N) rep(j,N) 
	   if (map[i][j]) f[i+1][j+N*2+1] = 1;
	   else f[i+N+1][j+N*3+1] = 1;
     rep(i,N) f[i+1][i+N+1] = K,f[i+N*3+1][i+N*2+1] = K;
     int cnt = 0;
     while (Build())
       while (Find(S,INF)) cnt += delta;
     return cnt == x*N;
}

int main()
{
 //	setIO("test");
	
	scanf("%d %d\n", &N, &K);
	rep(i,N) {
      rep(j,N) {
        c = getchar();
        map[i][j] = c == 'Y';
      }
      scanf("\n");
    }
	int l = 0,r = N+1;
    while (l + 1 < r) {
      int mid = (l+r) / 2;
      if (check(mid)) l = mid;
      else r = mid;
	}
    printf("%d\n", l);
	
	return 0;
}
