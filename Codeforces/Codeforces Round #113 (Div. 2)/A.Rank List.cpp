/*
  Task: Rank List
  Created: 2012.03.23
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

const int maxN = 50+10;
int N,K;
int P[maxN],T[maxN],Rank[maxN],num[maxN],C[maxN];

bool cmp(int a,int b)
{
 	 return (P[a] > P[b] || (P[b] == P[a] && T[a] < T[b]));
}

int main()
{ 	
 	scanf("%d %d", &N, &K);
	rep(i,N) scanf("%d %d", &P[i], &T[i]);
	rep(i,N) num[i] = i;
	sort(num,num + N,cmp);
	int cnt = 1;Rank[0] = 1;C[1] = 1;
	For(i,1,N-1) {
      ++cnt;
      if (P[num[i]] == P[num[i-1]] && T[num[i]] == T[num[i-1]])  Rank[i] = Rank[i-1];
	  else Rank[i] = cnt;
	  C[cnt] = Rank[i];
    }
    cnt = 0;K = C[K];
    rep(i,N) if (Rank[i] == K) ++cnt;
	printf("%d\n", cnt);
	
	return 0;
}
