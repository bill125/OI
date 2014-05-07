/*
  Task: C. Photographer
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

const int INF = 2147483647,maxN = 100000+10;
int N;
ll D;
struct Client
{
       ll M;
       int Num;
}A[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

bool cmp(Client a,Client b)
{
     return (a.M < b.M);
}

int main()
{
 	//setIO("test");
 	
 	scanf("%d %I64d", &N, &D);
 	int a,b;
 	scanf("%d %d", &a, &b);
    rep(i,N) {
      int x,y;
      scanf("%d %d", &x, &y);
      A[i].Num = i+1;A[i].M = x*a + y*b;
    }
    sort(A,A + N,cmp);
    ll cnt = 0;
    int ans = 0;
    rep(i,N) {
      cnt += A[i].M;
      if (cnt > D) break;
      ans = i+1;
    }
    printf("%d\n", ans);
    rep(i,ans) {
      printf("%d", A[i].Num);
      if (i == ans-1) printf("\n");
      else printf(" ");
    }
    
	return 0;
}
