/*
  Task: Replacing Digits
  Created: 2012.03.25
  Author: Zhu Jiahao
  Updated: 2012.03.26
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

const int maxN = 100000+10;
char c[maxN],t;
int f[10],a[maxN],b[maxN],f2[10];

int getlen(char c[])
{
 	rep(i,maxN) if (c[i] == 0) return i;
}

int main()
{
	scanf("%s\n", c); 
	int n = getlen(c);
	rep(i,n) a[i] = c[i] - '0';
	scanf("%s\n", c);
	int m = getlen(c);
	rep(i,m) b[i] = c[i] - '0';
	repD(i,10) {
      int cnt = 0;
      rep(j,m) if (b[j] == i) ++cnt; 
      rep(j,n) {
        if (cnt == 0) break;
		if (a[j] < i) a[j] = i,--cnt;
      }
	}
	int k;
	rep(i,n) if (a[i] != 0) {
      k = i;break;
    }
    rep(i,n-k) printf("%d", a[i+k]);
    printf("\n");
	return 0;
}
