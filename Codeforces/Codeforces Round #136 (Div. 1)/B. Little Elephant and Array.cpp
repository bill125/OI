/*
  Task: B. Little Elephant and Array
  Created: 2012.08.31
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

const int INF = 2147483647,maxN = 100000+10;
int N,M,tot;
int A[maxN],num[maxN],s[maxN],B[maxN],f[maxN][450];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

bool cmp(int a,int b)
{
	return A[a] < A[b];
}
int main()
{
 	//setIO("test"); 	
	
	scanf("%d %d", &N, &M);
	fill(num,0);
	For(i,1,N) scanf("%d", &A[i]),num[i] = i;
	sort(num+1,num + N+1,cmp);
	//rep(i,N+1) printf("%d\n", num[i]);
	rep(i,N+1) s[i] = -1;A[0] = -1;

	int cnt = -1,now = INF,tot = 0;
	For(i,1,N+1) if (A[num[i]] == now) ++cnt;
	else {
		if (cnt >= now) {
			For(j,i-cnt,i-1) s[num[j]] = tot;
			B[tot++] = now;
		}
		cnt = 1,now = A[num[i]];
	}
	//For(i,1,N) printf("%d\n", s[i]);
	//rep(j,tot) printf("%d ", B[j]);
	//printf("\n");
	rep(j,tot) f[0][j] = 0;
	For(i,1,N) {
		rep(j,tot) f[i][j] = f[i-1][j];
		if (s[i] != -1) ++f[i][s[i]];
	//	rep(j,tot) printf("%d ", f[i][j]);
		//printf("\n");
	}
	rep(i,M) {
		int a,b,ans = 0;
		scanf("%d %d", &a, &b);
		rep(j,tot) if (f[b][j] - f[a-1][j] == B[j]) ++ans;
		printf("%d\n", ans);
	}	
    
	return 0;
}