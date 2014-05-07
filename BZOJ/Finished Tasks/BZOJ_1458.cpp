/*
  Task: BZOJ_1458
  Created: 2012.04.12
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
#define ForE(i,a) for (int i = a;i != 0;i = next[i])
#define sqr(a) (a*a)
#define shl(a,b) (a << b)
#define shr(a,b) (a >> b)
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define lowbit(x) (x & -x)
#define abs(x) (x > 0 ? x : -x)
#define pb push_back

const int maxN = 100+10,maxP = 200+10,INF = 2147483647;
int N,M,K,delta,S,T;
int L[maxN],C[maxN],d[maxP],q[maxP],f[maxP][maxP];
bool v[maxP],Map[maxN][maxN];


void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

bool Build()
{
 	 fill(v,0);
 	 rep(i,T+1) d[i] = INF;
 	 int l = -1,r = 0;
	 q[0] = S,v[S] = true,d[S] = 0;
 	 while (l < r) {
       ++l;
       rep(i,T+1) 
         if (f[q[l]][i] && d[q[l]] + 1 < d[i]) {
           d[i] = d[q[l]] + 1;
           if (!v[i]) {
	         if (i == T) return true;
	         q[++r] = i;v[i] = true;
		   }
		 }
       v[q[l]] = false;
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
       if (d[x] + 1 == d[i] && f[x][i] && Find(i,min(now_flow,f[x][i])))  {
         f[x][i] -= delta;f[i][x] += delta;
         return true;
       }
     return false;
}

int main()
{
 //	setIO("test");
	
	scanf("%d %d %d", &M, &N, &K);
	rep(i,M) scanf("%d", &L[i]);
	rep(i,N) scanf("%d", &C[i]);
	int x,y;fill(Map,0);
	rep(i,K) {
      scanf("%d %d", &x ,&y);
      Map[--x][--y] = true;
    }
    rep(i,M) rep(j,N) if (!Map[i][j]) --L[i],--C[j];
    rep(i,M) if (L[i] > 0) {printf("JIONG!\n");return 0;}
    rep(i,N) if (C[i] > 0) {printf("JIONG!\n");return 0;}
    
	S = 0,T = N+M+1;
	rep(i,M) f[S][i+1] = -L[i];
    rep(i,M) rep(j,N) if (!Map[i][j]) f[i+1][j+M+1] = 1;
    rep(i,N) f[i+1+M][T] = -C[i];
    
	int ans = 0;
	while (Build())
	  while (Find(S,INF)) 
	    ans += delta;
	printf("%d\n", N*M-K-ans);
	
	return 0;
}
