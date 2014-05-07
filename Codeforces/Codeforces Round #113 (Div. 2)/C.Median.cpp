/*
  Task: Median
  Created: 2012.03.24
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != 0;i = next[i])
#define shl(a,b) (a << b)
#define shr(a,b) (a >> b)
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))

const int maxN = 500+10;
int N,X;
int S,L,E;

int main()
{
	scanf("%d %d", &N, &X);
	int k;
	rep(i,N) {
      scanf("%d", &k);
      if (k > X) ++L;
      if (k < X) ++S;
    }
	int ans = 0;
	while (true) {
      if (S < (N+1)/2 && L <= N-(N+1)/2) break;
      ++ans,++N;
	}
	printf("%d\n", ans);
	
	return 0;
}
