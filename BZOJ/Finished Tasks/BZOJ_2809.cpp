/*
  Task: BZOJ_2809
  Created: 2012.05.16
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

const int maxN = 100000+10,INF = 2147483647;
int N,M;
int num[maxN];
struct Ninja
{
 	   int B,C,Cnt;
 	   ll W,Len;
}A[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

bool cmp(int a,int b)
{
 	 return A[a].C < A[b].C;
}

void Update(int x)
{
 	 int t = A[x].C;
 	 while (x != -1) {
       if (t + A[x].Cnt <= M) A[x].Cnt += t,++A[x].Len;
       else return;
	   x = A[x].B;
	 }
}

int main()
{
 	//setIO("test");
 	
 	scanf("%d %d", &N, &M);
 	rep(i,N) scanf("%d %lld %lld", &A[i].B, &A[i].C, &A[i].W),num[i] = i,--A[i].B;
 	rep(i,N) A[i].Cnt = A[i].Len = 0;
 	
	sort(num,num + N,cmp);
	
	rep(i,N) Update(num[i]);
	
	ll ans = 0;
	rep(i,N) if (A[i].W * A[i].Len > ans) ans = A[i].W * A[i].Len; 
	printf("%lld\n", ans);
	
	return 0;
}
