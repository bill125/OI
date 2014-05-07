/*
  Task: BZOJ_1026
  Created: 2012.03.12
  Author: Zhu Jiahao
  Updated: 2012.03.13
*/

#include<cstdio>

using namespace std;

#define rep(i,n) for (i = 0;i < n;++i)
#define For(i,a,b) for (i = a;i <= b;++i)

const int maxLen = 12,maxNum = 10;
int i,j,k,l;
int s[maxLen+10];
long long A,B,C[maxLen+10][maxNum+10],sum[maxLen+10];

int abs(int x)
{
 	if (x > 0) return x;
 	else return -x;
}

long long work(int x,int last)
{
 	 if (x == 0) return 1;
 	 int i;
 	 long long cnt = 0;
 	 rep(i,s[x]) if (abs(i - last) >= 2) cnt += C[x][i];
 	 if (abs(s[x] - last) < 2) return cnt;
 	 else return cnt + work(x-1,s[x]);
}

long long solve(long long x)
{
 	 if (x == 0) return 1;
 	 int i,j,l = 0;
 	 while (x != 0) s[++l] = x % 10,x /= 10;
 	 long long cnt = sum[l-1];
 	 return cnt+work(l,-1);
}

int main()
{
 	rep(i,maxNum) C[1][i] = 1;sum[1] = 10;
 	For(i,2,maxLen-1) {
      sum[i] = sum[i-1];
      rep(j,maxNum) {
        C[i][j] = 0;
        rep(k,maxNum) if (abs(k-j) >= 2) C[i][j] += C[i-1][k];
        if (j != 0) sum[i] += C[i][j];
      }
    }
 	scanf("%lld %lld", &A, &B);
 	printf("%lld\n", solve(B) - solve(A-1));
 	
 	return 0;
}
