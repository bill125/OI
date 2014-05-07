/*
  Task: BZOJ_1025
  Created: 2012.03.12
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<cstring>

using namespace std;

#define rep(i,n) for (i = 0;i < n;++i)
#define For(i,a,b) for (i = a;i <= b;++i)
#define fill(a,b) memset(a,b,sizeof(a))

const int maxN = 1000+100;
int i,j,k,N,L,now;
long long ans;
int hash[maxN];
long long f[maxN][maxN];

void gethash()
{
 	 int i;L = 0;
 	 bool flag;
     For(i,2,N) {
       flag = true;
       For(j,1,L)
         if (i % hash[j] == 0) {
 	       flag = false; break;
         }
       if (flag) hash[++L] = i;
     }
}

int main()
{
 	scanf("%d", &N),++N;
 	gethash();
 	fill(f,0);f[0][0] = 1;
	For(i,1,L) 
      rep(j,N) {
        f[i][j] = f[i-1][j];now = hash[i];
        rep(k,N) {
		  if (now > j) break;
		  f[i][j] += f[i-1][j-now];
		  now *= hash[i];
	    }
	  }
	rep(i,N) ans += f[L][i];
	printf("%lld\n", ans);
 	
 	return 0;
}
