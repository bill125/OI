/*
  Task: Wizards and Numbers
  Created: 2012.03.30
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;
typedef long double ld; 
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
#define pb push_back

const int maxN = 10000+10;
int N;

bool solve(ll a,ll b)
{
    if (a == 0 || b == 0) return false;
 	if (!solve(b % a,a)) return true;
	return (b / a) % (a + 1) % 2 == 0; 
}

int main()
{
	scanf("%d", &N);
	rep(i,N) {
      ll a,b;
      scanf("%I64d %I64d", &a, &b);
	  if (solve(min(a,b),max(a,b))) printf("First\n");
	  else printf("Second\n"); 
	}
	
	return 0;
}
