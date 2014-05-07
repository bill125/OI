/*
  Task: BZOJ_1416
  Created: 2012.10.03
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != -1;i = E[i].next)
#define sqr(a) ((a)*(a))
#define shl(a,b) ((a) << (b))
#define shr(a,b) ((a) >> (b))
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back

const int INF = 2147483647,maxN = 1000+10,maxL = 10000;
int T,N,D,L;
ll a[maxN];
int ss[maxL],ans[maxL],s[2][maxL],l[2];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

ll gcd(ll a,ll b)
{
	if (a == 0) return b;
	return gcd(b % a,a);
}

void gethash()
{
	L = 0;
	For(i,2,20000) {
		bool flag = true;
		rep(j,L) if (i % ss[j] == 0) {
			flag = false;break;
		}
		if (flag) ss[L++] = i;
	}
}

int main()
{
 	//setIO("test"); 	
	
	gethash();
	//rep(i,L) printf("%d ", ss[i]);
	//printf("\n");
	scanf("%d %d %d", &T, &N, &D);
	ll all = 0;
	rep(i,T) scanf("%lld", &a[i]),all += a[i];
	fill(ans,0);
	rep(i,N) {
		ll x;int y;
		scanf("%d %d", &x, &y),--y;
		x = a[y];
		rep(i,L) while (x % ss[i] == 0) {
			x /= ss[i];++ans[i];
		}
		x = all;
		rep(i,L) while (x % ss[i] == 0) {
			x /= ss[i];--ans[i];
		}
		a[y] += D,all += D;
	}
	fill(s,0);
	l[0] = l[1] = 1,s[0][0] = s[1][0] = 1;
	/*rep(i,L) if (ans[i] != 0) {
		printf("%d %d\n", ss[i], ans[i]);
	}*/
	rep(i,L) {
		int q,x;
		if (ans[i] > 0) q = 0,x = ans[i];
		else if (ans[i] < 0) q = 1,x = -ans[i];
		else continue;	
		rep(p,x) {
			int k = 0;
			rep(j,l[q]) {
				k += s[q][j]*ss[i];
				s[q][j] = k %10;
				k /= 10;
			}
			while (k != 0) {
				s[q][l[q]++] = k % 10;
				k /= 10;
			}
			//repD(h,l[0]) printf("%d", s[0][h]);
			//printf("\n");
		}
	}
	repD(i,l[0]) printf("%d", s[0][i]);
	printf("/");
	repD(i,l[1]) printf("%d", s[1][i]);
	printf("\n");
    
	return 0;
}
