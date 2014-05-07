/*
  Task: A. Little Elephant and Rozdil
  Created: 2012.07.12
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
int N;
struct Town
{
       int S,num;
}A[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

bool cmp(Town a,Town b)
{
     return (a.S < b.S);
}

int main()
{
 	//setIO("test"); 	
 	
 	scanf("%d", &N);
 	rep(i,N) scanf("%d", &A[i].S),A[i].num = i+1;
 	sort(A,A+N,cmp);
 	if (N > 1 && A[0].S == A[1].S) printf("Still Rozdil\n");
 	else printf("%d\n", A[0].num);
    
	return 0;
}
