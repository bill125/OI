/*
  Task:
  Created:
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

const int INF = 2147483647,maxN = 52+10;
int N;
struct Card
{
       char s,v;
       int num;
}A[maxN];
int f[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

bool work(int v)
{
     if (v == 0) return true;
     int i = A[v].num,k;
     if (v >= 3) {
       k = A[v-3].num;
       if (A[i].s == A[k].s || A[i].v == A[k].v) {
         A[v-3].num = i;
         if (work(v-1)) return true;
         A[v-3].num = k;
       }
     }
     k = A[v-1].num;
     if (A[i].s == A[k].s || A[i].v == A[k].v) {
       A[v-1].num = i;
       if (work(v-1)) return true;
       A[v-1].num = k;
     }
     return false;
}

int main()
{
 	//setIO("test"); 	
    
    scanf("%d\n", &N);
    rep(i,N) scanf("%c%c ", &A[i].v, &A[i].s),A[i].num = i;
    
    if (work(N-1)) printf("YES\n");
    else printf("NO\n");
    
	return 0;
}
