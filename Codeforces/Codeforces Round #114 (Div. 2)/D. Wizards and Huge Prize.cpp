/*
  Task: Wizards and Huge Prize 
  Created: 2012.03.29
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;
typedef long double ld; 
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != 0;i = next[i])
#define sqr(a) (a*a)
#define shl(a,b) (a << b)
#define shr(a,b) (a >> b)
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back

const int maxN = 200+10;
int N,L,K;
db p[maxN],f[maxN],now[maxN][maxN],last[maxN][maxN];
int a[maxN],n1[maxN],n2[maxN];

int main()
{
	scanf("%d %d %d", &N, &L, &K);
	int x;
	rep(i,N) scanf("%d", &x),p[i] = (double)x / 100;;
	int l1 = 0,l2 = 0;
	rep(i,N) {
      scanf("%d", &a[i]);
	  if (a[i] == -1) n1[l1++] = i;
	  else n2[l2++] = i;
    }
    
    rep(i,l1+1) f[i] = 0;
    f[0] = 1;
    rep(i,l1) repD(j,i+2) 
	  if (j == 0) f[j] *= 1-p[n1[i]];
	  else f[j] = f[j-1]*p[n1[i]] + f[j]*(1-p[n1[i]]);
    last[0][0] = 1;
	rep(i,l2) {
      rep(j,l1+1) rep(k,i+1) now[j][k] = last[j][k]*(1-p[n2[i]]);
      rep(j,l1+1) rep(k,i+1) now[min(l1,j+a[n2[i]])][k+1] += last[j][k]*p[n2[i]];
	  rep(j,l1+1) rep(k,i+2) last[j][k] = now[j][k];
    }
    db ans = 0;
    rep(i,l1+1) For(j,max(0,i-K),l1) For(k,max(0,L-i),l2) ans += f[i] * last[j][k];
    printf("%.8lf\n", ans);
	
	return 0;
}
