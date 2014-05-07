/*
  Task: C. Little Elephant and Interval
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

const int INF = 2147483647,maxL = 18+10;
ll N1,N2;
ll f[maxL];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

ll solve(ll a)
{
     if (a == 0) return 0;
     ll l = 0,k = 1,res = 0;
     while (a >= k) ++l,k *= 10;
     k /= 10;
     ll x = a/k,y = a % 10;
     a %= k;a /= 10;
     if (x <= y) ++a;
     res = a;
     
     k = 1;
     rep(i,l-2) k *= 10;
     res += k*(x-1);
     
     res += f[l-1];
     
     return res;
}

int main()
{
 	//setIO("test"); 	
    
    f[0] = 0,f[1] = 9;
    ll k = 1;
    For(i,2,18) f[i] = 9*k+f[i-1],k *= 10; 
    scanf("%I64d %I64d", &N1, &N2);
    if (N2%10==0) --N2;
    ll a = solve(N2);
    ll b = solve(N1-1);
    printf("%I64d\n", a-b);
    
	return 0;
}
