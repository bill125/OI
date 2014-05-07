/*
  Task: Wizards and Demonstration
  Created: 2012.03.27
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

typedef long long ll;
typedef long double ld; 
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
#define pb push_back

int N,X,Y;

int main()
{
 	scanf("%d %d %d", &N, &X, &Y);
 	int k = N*Y;
 	if (k % 100 == 0) k /= 100;
 	else k = k / 100 + 1;
 	printf("%d\n", max(0,k-X));
	
	return 0;
}
