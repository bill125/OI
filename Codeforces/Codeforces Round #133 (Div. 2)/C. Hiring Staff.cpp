/*
  Task: C. Hiring Staff
  Created: 2012.08.14
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

const int INF = 2147483647;

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int main()
{	
	int N,M,K;
	scanf("%d %d %d", &N, &M, &K);
	int ans;
	if (K == 1) {
		if (N <= M+1) {
			if (N == 2 && M == 2) {
				printf("4\n");
				rep(i,4) printf("%d ", i+1);
				printf("\n");
			}
			else {
				printf("3\n");
				printf("1 %d %d", N, N+N-1);
			}
		}
		else {
			printf("2\n");
			printf("1 %d\n", N);
		}
	}
	else {
		if (N == M) {
			printf("%d\n", 2*K+1);
			rep(i,K) printf("1 ");
			rep(i,K-1) printf("%d ", N+1);
			printf("%d %d\n", N, N+2);
		}
		else {
			printf("%d\n", 2*K);
			rep(i,K) printf("1 ");
			rep(i,K-1) printf("%d ", N);
			printf("%d\n", N+1);
		}
	}
    
	return 0;
}
