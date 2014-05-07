/*
  Task: Burning Midnight Oil
  Created: 2012.03.16
  Author: Zhu Jiahao
*/

#include<cstdio>

using namespace std;

int mid,N,K,l,r;

bool check(int n)
{
 	 int cnt = 0;
 	 long long k = 1;
 	 while (k <= n) {
       cnt += n/k;
       k *= K;
	 }
	 if (cnt >= N) return true;
	 else return false;
}

int main()
{
 	scanf("%d %d", &N, &K);
 	l = 0;r = N;
 	while (l + 1 < r) {
      mid = (l+r) / 2;
      if (check(mid)) r = mid;
      else l = mid;
	}
	printf("%d\n", r);
 	
 	return 0;
}
