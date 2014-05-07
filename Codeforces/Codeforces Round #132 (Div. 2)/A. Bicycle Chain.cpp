/*
  Task: A. Bicycle Chain
  Created: 2012.08.06
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

const int INF = 2147483647,maxN = 50+10,maxM = 50+10;
int N,M;
int A[maxN],B[maxM];

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
	
	scanf("%d", &N);
	rep(i,N) scanf("%d", &A[i]);
	scanf("%d", &M);
	rep(i,M) scanf("%d", &B[i]);
	int ans = -INF,cnt = 0;
	rep(i,M) rep(j,N) if (B[i] % A[j] == 0) {
		if (B[i] / A[j] > ans) ans = B[i]/A[j],cnt = 1;
		else if (B[i] / A[j] == ans) ++cnt;
	}
	printf("%d\n", cnt);
    
	return 0;
}
