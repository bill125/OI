/*
  Task: BZOJ_1008
  Created: 2012.02.25
  Author: Zhu Jiahao
*/

#include<cstdio>

using namespace std;

const long long P = 100003;
long long N,M,ans;

long long Fast_Power(long long a,long long b)
{
 	long long res = 1;
 	a %= P;
 	while (b > 0) {
      if (b % 2 == 1) res = (a*res) % P;
	  b = b >> 1;a = (a*a) % P;
	}
	return res;
}

int main()
{
 	scanf("%lld%lld", &M, &N);
 	ans = (Fast_Power(M,N) + P - (Fast_Power(M-1,N-1) * M) % P) % P;
 	printf("%lld\n", ans);
 	
 	return 0;
}
