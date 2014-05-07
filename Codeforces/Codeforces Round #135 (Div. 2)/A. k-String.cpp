/*
  Task: A. k-String
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

const int INF = 2147483647,maxN = 1000+10;
int N,K,cnt[26];
char c[maxN],a[maxN];

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
	
	scanf("%d", &K);
	scanf("%s", c);
	N=strlen(c);
	rep(i,N) ++cnt[c[i]-'a'];
	int now = 0;
	rep(i,26) if (cnt[i] % K != 0) {
		printf("-1\n");
		return 0;
	}
	else {
		rep(j,cnt[i] / K) a[now++] = i+'a';
	}
	rep(j,K) rep(i,now) printf("%c", a[i]);
	printf("\n");
    
	return 0;
}
