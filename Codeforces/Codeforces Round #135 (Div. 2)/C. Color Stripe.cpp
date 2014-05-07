/*
  Task: C. Color Stripe
  Created: 2012.08.27
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

const int INF = 2147483647,maxN = 500000+10;
int N,K;
char c[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int main()
{
 	//setIO("test"); 	
	
	scanf("%d %d", &N, &K);
	scanf("%s", c);
	rep(i,N) c[i] -= 'A';
	if (K == 2) {
		int ans = N,now = 0;
		rep(i,N) if (c[i] == i % 2) ++now;
		ans = min(ans,now);
		now = 0;
		rep(i,N) if (c[i] != i % 2) ++ now;
		if (now < ans) {
			printf("%d\n", now);
			rep(i,N)	printf("%c", i%2+'A');
			printf("\n");
		}
		else {
			printf("%d\n", ans);
			rep(i,N) printf("%c", (i+1)%2+'A');
			printf("\n");
		}
	}
	else {
		int ans = 0;
		For(i,1,N-2) if (c[i] == c[i-1] && c[i] == c[i+1]) {
			rep(j,K) if (j != c[i-1] && j != c[i+1]) {
				c[i] = j;break;
			}
			++ans;
		}
		c[N] = -1;
		For(i,1,N-1) if (c[i] == c[i-1] || c[i] == c[i+1]) {
			rep(j,K) if (j != c[i-1] && j != c[i+1]) {
				c[i] = j;break;
			}
			++ans;
		}
		printf("%d\n",ans);
		rep(i,N) printf("%c", c[i]+'A');
		printf("\n");
	}
    
	return 0;
}
