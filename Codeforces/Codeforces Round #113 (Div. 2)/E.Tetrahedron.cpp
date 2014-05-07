/*
  Task: Tetrahedron	
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

const int maxV = 4+10;
long long last[maxV],now[maxV];
long long P = 1000000007;
int N;

int main()
{
	scanf("%d", &N);
    rep(i,4) last[i] = 0;
    last[0] = 1;
    long long cnt = 1;
	rep(p,N) {
      rep(i,4) now[i] = (cnt-last[i]+P)%P;
      cnt = 0;
      rep(i,4) last[i] = now[i],cnt+=now[i];
    }
    printf("%d\n", now[0]);
	
	return 0;
}
