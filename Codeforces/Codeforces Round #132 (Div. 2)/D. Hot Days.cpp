/*
  Task: D. Hot Days
  Created: 2012.08.06
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

const int INF = 2147483647;
int N,M;

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
	ll ans = 0;
	rep(i,N) {
		ll a,b,c,d;
		scanf("%I64d %I64d %I64d %I64d", &a, &b, &c, &d);
		ll t = b-a,t2;
		if (t <= 0) ans += M*c+d;
		else {
			if (M % t == 0) t2 = M / t ;
			else t2 = M / t+1;
			ans += min(M*c+d,t2*d);
		}
	}
	printf("%I64d\n", ans);
    
	return 0;
}
