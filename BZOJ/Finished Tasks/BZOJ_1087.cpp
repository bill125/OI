/*
  Task: BZOJ_1087
  Created: 2012.07.01
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

const int INF = 2147483647,maxN = 9+10,maxM = shl(1,9)+10,maxK = 81+10;
int N,K;
bool Match[maxM][maxM],V[maxM];
int Num[maxM];
ll f[maxN][maxM][maxK];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int lowbit(int x)
{
    return x & -x;
}

bool check(int x)
{
     int last = 0;
     while (x != 0) {
       int now = lowbit(x);
       if (now == last*2) return false;
       last = now,x -= now;
     }
     return true;
}

void Pre_Work(int M)
{
     rep(i,M) V[i] = check(i);
     rep(i,M) rep(j,M) 
       Match[i][j] = (check(i|j)) && ((i & j) == 0);
     rep(i,M) {
       int j = i;
       while (j != 0) ++Num[i],j -= lowbit(j);
     }
}

int main()
{
 	//setIO("test");
 	
 	scanf("%d %d", &N, &K);
 	Pre_Work(shl(1,N));
 	fill(f,0);
 	f[0][0][0] = 1;
    For(i,1,N) rep(j,shl(1,N)) if (V[j])
      rep(l,K+1) rep(k,shl(1,N)) if (Match[k][j] && l >= Num[j] + Num[k]) 
        f[i][j][l] += f[i-1][k][l-Num[j]];
        
    ll ans = 0;
    rep(i,shl(1,N)) ans += f[N][i][K];
    printf("%lld\n", ans);
    
	return 0;
}
