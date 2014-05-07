/*
  Task: BZOJ_1677
  Created: 2012.04.23
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

const int maxN = 1000000+10,maxK = 20+10,INF = 2147483647,P = 1000000000;
int N;
ll f[maxN];

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
 	
 	scanf("%d", &N);
 	int K = 0;
	while (shl(1,K) <= N) ++K;
	f[0] = 1;
	rep(i,K) {
      int k = shl(1,i);
      rep(j,N+1) if (j - k >= 0) f[j] = (f[j-k]+f[j]) % P;
    }
    printf("%lld\n", f[N]);
	
	return 0;
}
