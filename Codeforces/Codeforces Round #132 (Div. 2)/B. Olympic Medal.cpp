/*
  Task: B. Olympic Medal
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

const int INF = 2147483647,maxM = 5000+10,maxK = 5000+10;
int N,M,K,A,B;

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int main()
{
 	setIO("test"); 	
	scanf("%d", &N);
	ll r1 = 0,p1 = 0,p2 = 5001;
	rep(i,N) {
		int a;
		scanf("%d", &a);
		if (a > r1) r1 = a;
	}
	scanf("%d", &M);
	rep(i,M) {
		int a;
		scanf("%d", &a);
		if (a > p1) p1 = a;
	}
	scanf("%d",  &K);
	rep(i,K) {
		int a;
		scanf("%d", &a);
		if (a < p2) p2 = a;
	}
	scanf("%d %d", &A, &B);
	
	int t = r1*r1*B*p1;
	db r2 = sqrt((db)t/(A*p2+B*p1));
	printf("%.10lf\n", r2);
    
	return 0;
}
