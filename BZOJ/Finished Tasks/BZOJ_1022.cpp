/*
  Task: BZOJ_1022
  Created: 2012.03.12
  Author: Zhu Jiahao
*/

#include<cstdio>

using namespace std;

#define rep(i,n) for (i = 0;i < n;++i)

int i,k,N,T,cnt,a;

void Judge(bool x)
{
 	 if (x == 0) printf("Brother\n");
 	 else printf("John\n");
}

int main()
{
    scanf("%d", &T);
 	while (T--) {
      scanf("%d", &N),cnt = 0,a = 0;
      rep(i,N) scanf("%d", &k),cnt ^= k,a += k == 1;
      if (a == N) Judge(!(a&1));
	  else Judge(cnt);
    }
    
    return 0;
}
