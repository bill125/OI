/*
  Task: BZOJ_1041
  Created: 2012.04.04
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

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

ll r,n,m;
typedef pair<int,int> ii;
set<ii> S;
int Cal(int d)
{
    long long r=::r/d;
    n = 1,m = 1;
	while (m*m < r)m++;
    while (n < m) {
      while (n < m && n*n+m*m > r) m--;
      if (n >= m)break;
      if (n*n+m*m == r){
	    int a = m*m-n*n,b = 2*m*n;
	    S.insert(ii(a*d,b*d));S.insert(ii(b*d,a*d));
	  }
      n++;
    }
}
int main()
{
    scanf("%d", &r);
    for(d,1,r) {
      if (d*d > r) break;
	  if (r%d == 0) Cal(r/d)+Cal(d);
	}
    if(d*d == r)Cal(d);
    printf("%d\n", S.size()*4+4);
}

